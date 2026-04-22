/// Open all files under a specified directory and print the records found
// there in for some time.

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#include "helpers.hpp"
#include "options.hpp"
#include "socketreader.hpp"

static void CloseFiles(std::vector<std::ifstream>& ifstreams);
//static void FifoReader(const Options& opts);
static void FileReader(const Options& opts);
static std::vector<std::string> FindFiles(const std::string& base_dir);
static std::vector<std::ifstream> OpenFiles(const std::string& base_dir);
static void PrintOptions(const Options& opts);
static void PrintUsage(void);
static void ReadFromFiles(std::vector<std::ifstream>& ifstreams, size_t num_seconds);
static void SocketServer(const Options& opts);

/// @brief Open files and print their contents for some time.
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

        AdjustLimits();

        if (opts.port > 0) {
            SocketServer(opts);
        } else {
            FileReader(opts);
        }
    } catch (const std::exception& ex) {
        Err("Error: %s", ex.what());
        return 1;
    }

    Msg("Done");
    return 0;
}

/// @brief Close the file streams.
/// @param ifstreams A vector of open file streams.
static void CloseFiles(std::vector<std::ifstream>& ifstreams)
{
    for (auto& ifs : ifstreams) {
        ifs.close();
    }
}

// static void PipeReader(const Options& opts)
// {
//     /// Create a named pipe and read messages from it,
//     /// printing them to standard output.
//     throw std::runtime_error("PipeReader not implemented");
// }

/// @brief Read from files under the base directory and print their contents.
/// Uses options::base_dir, options::delay_msec, options::num_files,
/// options::num_seconds, options::partition, options::wait_seconds, and
/// options::text_file.
/// @param opts Program options.
static void FileReader(const Options& opts)
{
        Msg("Opening files under: %s", opts.base_dir.c_str());
        std::vector<std::ifstream> ifstreams = OpenFiles(opts.base_dir);
        Msg("Found %zu files", ifstreams.size());

        Msg("Reading from files");
        ReadFromFiles(ifstreams, opts.num_seconds);

        Msg("Closing files");
        CloseFiles(ifstreams);
}

/// @brief Recursively find regular files under the base directory.
/// @param base_dir The base directory to search for files.
/// @return A vector of file paths.
static std::vector<std::string> FindFiles(const std::string& base_dir)
{
    std::vector<std::string> filenames;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(base_dir)) {
        if (entry.is_regular_file()) {
            filenames.push_back(entry.path().string());
        }
    }
    return filenames;
}

/// @brief Open all files under the base directory.
/// @param base_dir The base directory to search for files.
/// @return A vector of open file streams.
static std::vector<std::ifstream> OpenFiles(const std::string& base_dir)
{
    std::vector<std::string> filenames = FindFiles(base_dir);
    std::vector<std::ifstream> ifstreams;
    ifstreams.reserve(filenames.size());

    for (const auto& filename : filenames) {
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            continue;
        }
        ifstreams.push_back(std::move(ifs));
    }

    return ifstreams;
}

/// @brief  Print relevant options if verbose is enabled.
/// @param opts Program options.
static void PrintOptions(const Options& opts)
{
    if (opts.verbose) {
        std::cout << "Options:" << std::endl
            << "  -h  print_usage : " << (opts.print_usage ? "true" : "false") << std::endl
            << "  -v  verbose     : " << (opts.verbose ? "true" : "false") << std::endl
            << "  -n  num_files   : " << opts.num_files << std::endl
            << "  -s  num_seconds : " << opts.num_seconds << std::endl
            << "  -p  port        : " << opts.port << std::endl
            << "  -W  wait_method : " << opts.wait_method << std::endl
            << "  -d  base_dir    : " << opts.base_dir << std::endl
            << std::endl;
    }
}

/// @brief  Print usage information to the standard output stream.
static void PrintUsage(void)
{
    static const char USAGE[] =
        "Usage: reader [OPTIONS]\n"
        "\n"
        "Reads from N files or sockets for S seconds and writes to the console.\n"
        "If port is non-zero, it listens on that port for incoming connections.\n"
        "Otherwise, it reads from all files found under the base directory. \n"
        "\n"
        "Options:\n"
        "  -h, --help               Print this help message and exit\n"
        "  -v, --verbose            Enable extra runtime messages\n"
        "  -n, --num-files N        Number of files to read or connections to accept (default: 1)\n"
        "  -p, --port N             Port number to listen on [1025, 65535].  (default: 0)\n"
        "  -s, --seconds N          Number of seconds to run the program (default: 60)\n"
        "  -W, --wait-method MTHD   Wait method to use { epoll, poll, select } (default: poll)\n"
        "  -d, --directory DIR      Base directory to read files under (default: /tmp/poll)\n";


    std::cout << USAGE << std::endl;
}

static void ReadFromFiles(std::vector<std::ifstream>& ifstreams, size_t num_seconds)
{
    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(num_seconds)) {
        /// Use poll(2) to wait for files to be ready for reading
    }
}

static void SocketServer(const Options& opts)
{
    switch (ParseWaitMethod(opts.wait_method)) {
        case WaitMethod::Select:
            SocketServerSelect(opts);
            break;
        case WaitMethod::Poll:
            SocketServerPoll(opts);
            break;
        case WaitMethod::Epoll:
            SocketServerEpoll(opts);
            break;
        default:
            throw std::invalid_argument("wait_method");
            break;
    }
}
