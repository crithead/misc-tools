/**
 * Program Options.
 */

#include <getopt.h>

#include <algorithm>
//#include <cstddef>
#include <cstring>
#include <limits>
#include <stdexcept>

#include "options.hpp"

static size_t ParseLines(const char* arg);

/// Default average delay between writes (milliseconds).
const size_t Options::DEFAULT_DELAY_MSEC = 10;
const size_t Options::MIN_DELAY = 1;
const size_t Options::MAX_DELAY = 1000;

/// Default number of files to create.
const size_t Options::DEFAULT_NUM_FILES = 128;
const size_t Options::MIN_FILES = 1;
const size_t Options::MAX_FILES = 65535;

/// Default number of lines to send.
const size_t Options::DEFAULT_LINES = 0;
const size_t Options::MIN_LINES = 0;
const size_t Options::MAX_LINES = std::numeric_limits<size_t>::max();

/// Default number of seconds to run the program.
const size_t Options::DEFAULT_NUM_SECONDS = 60;
const size_t Options::MIN_SECONDS = 1;
const size_t Options::MAX_SECONDS = 3600;

// Default maximum number of files per directory.
const size_t Options::DEFAULT_PARTITION = 256;
const size_t Options::MIN_PARTITION = 32;
const size_t Options::MAX_PARTITION = 65355;

const size_t Options::DEFAULT_PORT = 0;
const size_t Options::MIN_PORT = 1025;
const size_t Options::MAX_PORT = 65535;

// Default number of seconds to wait between creating files and writing to them.
const size_t Options::DEFAULT_WAIT_SECONDS = 10;
const size_t Options::MIN_WAIT_SECONDS = 0;
const size_t Options::MAX_WAIT_SECONDS = 60;

/// Default base directory for created files.
const std::string Options::DEFAULT_BASE_DIR = "/tmp/poll";

/// Default text file to read from.
const std::string Options::DEFAULT_IP_ADDR = "127.0.0.1";

/// Default text file to read from.
const std::string Options::DEFAULT_TEXT_FILE = "/work/tmp/pg996.txt";

/// Default wait method.
const std::string Options::DEFAULT_WAIT_METHOD = "none";

/// @brief Parse command line options into this object.
/// @param argc Argument count
/// @param argv Argument vector
/// @throws std::invalid_argument if an unknown option is encountered.
Options::Options(int argc, char* argv[]) :
    print_usage(false),
    verbose(false),
    delay_msec(DEFAULT_DELAY_MSEC),
    lines(DEFAULT_LINES),
    num_files(DEFAULT_NUM_FILES),
    num_seconds(DEFAULT_NUM_SECONDS),
    partition(DEFAULT_PARTITION),
    port(DEFAULT_PORT),
    wait_seconds(DEFAULT_WAIT_SECONDS),
    base_dir(DEFAULT_BASE_DIR),
    ip_addr(DEFAULT_IP_ADDR),
    text_file(DEFAULT_TEXT_FILE),
    wait_method(DEFAULT_WAIT_METHOD)
{
    static struct option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"verbose", no_argument, nullptr, 'v'},
        {"address", required_argument, nullptr, 'a'},
        {"delay", required_argument, nullptr, 'D'},
        {"lines", required_argument, nullptr, 'l'},
        {"number-of-files", required_argument, nullptr, 'n'},
        {"partition", required_argument, nullptr, 'P'},
        {"port", required_argument, nullptr, 'p'},
        {"seconds", required_argument, nullptr, 's'},
        {"text-file", required_argument, nullptr, 't'},
        {"wait", required_argument, nullptr, 'w'},
        {"wait-method", required_argument, nullptr, 'W'},
        {"directory", required_argument, nullptr, 'd'},
        {nullptr, 0, nullptr, 0}
    };

    extern char *optarg;

    int opt;
    while ((opt = getopt_long(argc, argv, "a:D:d:hl:n:p:P:s:t:vw:W:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                print_usage = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'a':
                ip_addr = optarg;
                break;
            case 'd':
                base_dir = optarg;
                break;
            case 'D':
                delay_msec = std::clamp(std::stoul(optarg), MIN_DELAY, MAX_DELAY);
                break;
            case 'l':
                lines = ParseLines(optarg);
                break;
            case 'n':
                num_files = std::clamp(std::stoul(optarg), MIN_FILES, MAX_FILES);
                break;
            case 'P':
                partition = std::clamp(std::stoul(optarg), MIN_PARTITION, MAX_PARTITION);
                break;
            case 'p':
                port = std::clamp(std::stoul(optarg), MIN_PORT, MAX_PORT);
                break;
            case 's':
                num_seconds = std::clamp(std::stoul(optarg), MIN_SECONDS, MAX_SECONDS);
                break;
            case 't':
                text_file = optarg;
                break;
            case 'w':
                wait_seconds = std::clamp(std::stoul(optarg), MIN_WAIT_SECONDS, MAX_WAIT_SECONDS);
                break;
            case 'W':
                wait_method = optarg;
                break;
            default:
                throw std::invalid_argument("Unknown option");
                break;
        }
    }
}

/// @brief Parse a lines argument, which may have an optional suffix [kKmMgG].
/// @param arg The lines argument as a string.
/// @return The number of lines.
size_t ParseLines(const char* arg)
{
    if (arg[0] == '-') {
        throw std::invalid_argument("Lines must be a non-negative integer");
    }
    // Get the suffix and multiplier.
    size_t len = std::strlen(optarg);
    size_t f = 1;
    if (optarg[len - 1] == 'k' || optarg[len - 1] == 'K') {
        optarg[len - 1] = '\0';
        f *= 1024;
    } else if (optarg[len - 1] == 'm' || optarg[len - 1] == 'M') {
        optarg[len - 1] = '\0';
        f *= 1024 * 1024;
    } else if (optarg[len - 1] == 'g' || optarg[len - 1] == 'G') {
        optarg[len - 1] = '\0';
        f *= 1024 * 1024 * 1024;
    }
    size_t value = std::stoul(optarg);
    if (value > Options::MAX_LINES / f) {
        throw std::invalid_argument("Too many lines");
    } else {
        value *= f;
    }

    return std::clamp(value, Options::MIN_LINES, Options::MAX_LINES);
}

/// @brief Convert a wait method string to an enumeration value.
/// @param method The wait method as a string.
/// @return The corresponding wait method enum value.
WaitMethod ParseWaitMethod(const std::string& method)
{
    WaitMethod value = WaitMethod::None;

    if (method == "select") {
        value = WaitMethod::Select;
    } else if (method == "poll") {
        value = WaitMethod::Poll;
    } else if (method == "epoll") {
        value = WaitMethod::Epoll;
    } else {
        // Default to poll.
        return WaitMethod::Poll;
    }
    return value;
}
