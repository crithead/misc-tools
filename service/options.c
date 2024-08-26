
#include <getopt.h>
#include <stddef.h>

#include "options.h"

int init_options(int argc, char **argv, struct options *opts)
{
    if (opts == NULL) {
        return 1;
    }

    /* Set defaults */
    opts->help = false;
    opts->quiet = false;
    opts->verbose = false;
    opts->config_file = DEFAULT_CONFIG_FILE;

    static const char SHORT_OPTIONS[] = "c:hqv";
    static struct option LONG_OPTIONS[] = {
        {"config-file", required_argument,  0,  'c' },
        {"help",        no_argument,        0,  'h' },
        {"quiet",       no_argument,        0,  'q' },
        {"verbose",     no_argument,        0,  'v' },
        {0,             0,                  0,   0 }
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &option_index);

    while (c != -1) {
        switch (c) {
        case 'c':
            opts->config_file = optarg;
            break;
        case 'h':
            opts->help = true;
            break;
        case 'q':
            opts->quiet = true;
            break;
        case 'v':
            opts->verbose = true;
            break;
        default:
            break;
        }
        c = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &option_index);
    }

    return 0;
}
