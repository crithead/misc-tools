/*
 * Unix-domain UDP server.
 */

#include <stdarg.h>
#include <stdio.h>

#include "helpers.h"
#include "options.h"
#include "server.h"


static void print_usage(void);
static int run_server(struct options *);

int main(int argc, char **argv)
{
    struct options opts;
    init_options(argc, argv, &opts);

    if (opts.help) {
        print_usage();
        return 0;
    }

    if (opts.verbose) {
        enable_messages(true);
    }

    return run_server(&opts);
}

static void print_usage(void)
{
    static const char USAGE[] = "\n\
        server [ -hv ] [ -c config-file ]\n\
\n\
        -h, --help      Print a usage message and exit\n\
        -v, --verbose   Enable verbose output\n\
        -c FILE, --config-file FILE\n\
                        Read configuration from this file\n\
\n";

    puts(USAGE);
    printf("Version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

static int run_server(struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }
    msg("server start");

    

    msg("server exit");
    return 0;
}

