
#include <getopt.h>
#include <stddef.h>
#include <stdlib.h>

#include "options.h"

int init_options(int argc, char **argv, struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    /* Set defaults */
    opts->help = false;
    opts->quit = false;
    opts->verbose = false;
    opts->port = DEFAULT_SERVER_PORT;
    opts->socket_file = DEFAULT_SOCKET_FILE;

    static const char SHORT_OPTIONS[] = "hp:qs:v";
    static struct option LONG_OPTIONS[] = {
            {"socket-file", required_argument, 0, 's'},
            {"port", required_argument, 0, 'p'},
            {"help", no_argument, 0, 'h'},
            {"quit", no_argument, 0, 'q'},
            {"verbose", no_argument, 0, 'v'},
            {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &option_index);

    while (c != -1) {
        switch (c) {
        case 'h':
            opts->help = true;
            break;
        case 'p':
            opts->port = atoi(optarg);
            break;
        case 'q':
            opts->quit = true;
            break;
        case 's':
            opts->socket_file = optarg;
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
