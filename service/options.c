#include "options.h"

int init_options(int argc, char **argv, struct options *opts)
{
    if (opts == NULL) {
        return 1;
    }

    /* Set defaults */
    opts->quiet = false;
    opts->verbose = false;
    opts->config_file = DEFAULT_CONFIG_FILE;

    // TODO: Use getopt_long to parse the command line arguments

    return 0;
}
