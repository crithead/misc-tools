/**
 * Option processing for the daemon template.
 */
#pragma once

#include <stdbool.h>

/** Default file name of the configuration file. */
#define DEFAULT_CONFIG_FILE "/etc/templated.conf"

/**
 * Program runtime options.
 */
struct options {
    /** Print usage information and exit. */
    bool help;
    /** Set log level to WARNING. Overrides verbose. */
    bool quiet;
    /** Set log level to debug. */
    bool verbose;
    /** Path of the service's configuration file */
    const char *config_file;
};

/**
 * Parse command line arguments.
 * @param argc The argument count from main.
 * @param argv The argument vector from main.
 * @param opts The options structure to initialize.
 * @retval 0 Success
 * @retval 1 Failure
 */
extern int init_options(int argc, char **argv, struct options *opts);

