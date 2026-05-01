/// Create a set of files under a specified directory and write records
// to them periodically for some time.

#include <signal.h>

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#include "helpers.hpp"
#include "namer.hpp"
#include "options.hpp"
#include "socketwriter.hpp"
#include "textsource.hpp"

static std::vector<std::ofstream> CreateFiles(const std::string& base_dir, size_t num_files, size_t partition);
static void CloseFiles(std::vector<std::ofstream>& ofs);
static void FileWriter(const Options& opts);
static void GenerateFilenames(std::vector<std::string>& filenames, const std::string& base_dir, size_t num_files, size_t partition);
static void HandleSignals(void);
static void PrintOptions(const Options& opts);
static void PrintUsage(void);
static void WriteToFiles(std::vector<std::ofstream>& ofstreams, const std::string& textfile, size_t delay_msec, size_t num_seconds);

/// @brief Create files and write to them periodically for some time.
/// @param argc Argument count
/// @param argv Argument vector
/// @retval 0 Success
/// @retval 1 Failure
int main(int argc, char *argv[]) {
    try {
        Options opts(argc, argv);

        PrintOptions(opts);

        if (opts.print_usage) {
            PrintUsage();
            return 0;
        }

        if (opts.verbose) {
            EnableMessages(true);
        }

        HandleSignals();
        AdjustLimits();

        if (opts.port > 0) {
            SocketWriter(opts);
        } else {
            FileWriter(opts);
        }

    } catch (const std::invalid_argument& e) {
        Err("Invalid argument: %s", e.what());
        return 1;
    } catch (const std::exception& e) {
        Err("Error: %s", e.what());
        return 1;
    } catch (...) {
        Err("Unknown error");
        return 1;
    }

    Msg("Done");
    return 0;
}

/// @brief Create and open a set of files.
/// @param[in] base_dir The base directory to create files under.
/// @param[in] num_files The number of files to create.
/// @param[in] partition The maximum number of files per directory.
/// @return A vector of open file streams.
static std::vector<std::ofstream> CreateFiles(const std::string& base_dir, size_t num_files, size_t partition)
{
    std::vector<std::string> filenames;
    std::vector<std::ofstream> ofstreams;
    filenames.reserve(num_files);
    ofstreams.reserve(num_files);

    if (!DirectoryExists(base_dir)) {
        CreateDirectory(base_dir);
    }

    GenerateFilenames(filenames, base_dir, num_files, partition);

    // Open the files and save their stream objects.
    for (const auto& filename : filenames) {
        CreateDirectory(filename.substr(0, filename.find_last_of('/')));
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Failed to create file: " + filename);
        }
        ofstreams.push_back(std::move(ofs));
    }

    return ofstreams;
}

/// @brief Close the file streams.
/// @param[in] ofstreams A vector of file streams.
static void CloseFiles(std::vector<std::ofstream>& ofstreams)
{
    for (auto& os : ofstreams) {
        os.close();
    }
}

/// @brief  Write to files under the base directory periodically for some time.
/// Uses options::base_dir, options::delay_msec, options::num_files,
/// options::num_seconds, options::partition, options::wait_seconds, and
/// options::text_file.
/// @param[in] opts Program options.
static void FileWriter(const Options& opts)
{
    Msg("Creating %d files", opts.num_files);
    std::vector<std::ofstream> ofstreams = CreateFiles(opts.base_dir, opts.num_files, opts.partition);

    Msg("Pause for %d seconds", opts.wait_seconds);
    Pause(opts.wait_seconds * 1000);    // Pause in milliseconds

    Msg("Writing to files");
    WriteToFiles(ofstreams, opts.text_file, opts.delay_msec, opts.num_seconds);

    Msg("Closing files");
    CloseFiles(ofstreams);
}

/// @brief Generate file names under the base directory.
/// @param[out] filenames A vector to store the generated filenames.
/// @param[in] base_dir The base directory to create files under.
/// @param[in] num_files The number of files to open.
/// @param[in] partition The maximum number of files per directory.
static void GenerateFilenames(std::vector<std::string>& filenames, const std::string& base_dir, size_t num_files, size_t partition)
{
    static constexpr size_t NAME_LENGTH = 12;
    Namer namer(NAME_LENGTH);

    if (num_files <= partition) {
        // all files in base directory
        for (size_t i = 0; i < num_files; ++i) {
            std::string file_path = base_dir + "/" + namer.GetName();
            filenames.push_back(file_path);
        }
    } else {
        // one level of subdirectories
        size_t n = num_files;
        while (n > 0) {
            std::string dir = base_dir + "/" + namer.GetName();
            size_t files_per_dir = std::min(partition, n);
            for (size_t i = 0; i < files_per_dir; i++) {
                std::string file_path = dir + "/" + namer.GetName() + ".txt";
                filenames.push_back(file_path);
            }
            // prevent wrap around of unsigned number
            n = n > partition ? n - partition : 0;
        }
    }
}

/// @brief Install signal handlers.
static void HandleSignals(void)
{
    Msg("Install signal handlers");

    struct sigaction sa;
    sa.sa_handler = [](int signum) {
        switch (signum) {
            case SIGINT:
                Err("SIGINT (%d)", signum);
                exit(2);
                break;
            case SIGPIPE:
                Err("SIGPIPE (%d)", signum);
                break;
            default:
                Err("signal %d", signum);
                break;
        }
    };
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    int e = sigaction(SIGINT, &sa, nullptr);
    if (e == -1) {
        throw std::runtime_error("sigaction: " + std::string(strerror(errno)));
    }
    e = sigaction(SIGPIPE, &sa, nullptr);
    if (e == -1) {
        throw std::runtime_error("sigaction: " + std::string(strerror(errno)));
    }
}

/// @brief  Print the options if verbose is enabled.
/// @param opts Program options.
static void PrintOptions(const Options& opts)
{
    if (opts.verbose) {
        std::cout << "Options:" << std::endl
            << "  -h  print_usage  : " << (opts.print_usage ? "true" : "false") << std::endl
            << "  -v  verbose      : " << (opts.verbose ? "true" : "false") << std::endl
            << "  -D  delay_msec   : " << opts.delay_msec << std::endl
            << "  -l  lines        : " << opts.lines << std::endl
            << "  -n  num_files    : " << opts.num_files << std::endl
            << "  -s  num_seconds  : " << opts.num_seconds << std::endl
            << "  -P  partition    : " << opts.partition << std::endl
            << "  -p  port         : " << opts.port << std::endl
            << "  -w  wait_seconds : " << opts.wait_seconds << std::endl
            << "  -d  base_dir     : " << opts.base_dir << std::endl
            << "  -t  text_file    : " << opts.text_file << std::endl
            << std::endl;
    }
}

/// @brief  Print usage information to the standard output stream.
static void PrintUsage(void)
{
    static const char USAGE[] =
        "Usage: writer [OPTIONS]\n"
        "\n"
        "File Writer: Create N files under the base directory, wait W seconds, then\n"
        "write to one file chosen at random every D milliseconds for S seconds.\n"
        "\n"
        "    writer -n 100 -P 16 -s 90 -w 10 -t /tmp/input.txt\n"
        "\n"
        "Socket Writer (enabled if port is non-zero): Open N socket connections\n"
        "to the server at port P, then write to one connection chosen at random every D\n"
        "milliseconds for S seconds.\n"
        "\n"
        "    writer -n 100 -s 60 -p 2025 -D 100 -t /tmp/input.txt\n"
        "\n"
        "If the value of lines is non-zero, write N lines of text instead of writing\n"
        "for a number of seconds. For example: write 1 million lines of text with a\n"
        "delay of 0 ms.\n"
        "\n"
        "    writer -n 100 -l 1M -p 2025 -D 0 -t /tmp/input.txt\n"
        "\n"
        "Options:\n"
        "  -h, --help               Print this help message and exit\n"
        "  -v, --verbose            Enable extra messages\n"
        "  -D, --delay N            Average delay between writes in milliseconds (default: 10)\n"
        "  -l, --lines N            Number of lines to write (default: 0)\n"
        "  -n, --number-of-files N  Number of files to create or socket connections to open (default: 128)\n"
        "  -P, --partition N        Max number of files per directory (default: 256)\n"
        "  -p, --port P             Port number for socket connections (default: 0)\n"
        "  -s, --seconds N          Number of seconds to run the program (default: 60)\n"
        "  -t, --text-file FILE     Path to the text file to read from (default: /tmp/poll/input.txt)\n"
        "  -w, --wait N             Number of seconds to wait between creating files\n"
        "                           and writing to them (default: 10)\n"
        "  -d, --directory DIR      Base directory to create files under (default: /tmp/poll)\n";

    std::cout << USAGE << std::endl;
}

/// @brief
/// @param ofstreams A vector of open file streams.
/// @param textfile The path to the text file to read from.
/// @param delay_msec The average delay between writes in milliseconds.
/// @param num_seconds The number of seconds to write data to files.
static void WriteToFiles(std::vector<std::ofstream>& ofstreams,
    const std::string& textfile, size_t delay_msec, size_t num_seconds)
{
    size_t total_time_ms = 0;
    TextSource txtsrc(textfile);

    Msg("WriteToFiles every %zd ms for %zu seconds", delay_msec, num_seconds);
    while (total_time_ms < num_seconds * 1000) {

        size_t idx = RandInt(0, ofstreams.size() - 1);
        std::ofstream& ofs = ofstreams[idx];
        if (ofs.good()) {
            std::string text = txtsrc.GetText();
            text += '\n';   // put the newline back
            ofs.write(text.c_str(), text.length());
            ofs.flush();
        } else {
            Err("File stream #%d is not good", idx);
        }

        size_t delay = static_cast<size_t>(RandInt(2 * delay_msec / 3, 4 * delay_msec / 3));
        Pause(delay);
        total_time_ms += delay;
    }
}
