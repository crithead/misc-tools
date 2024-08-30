/*
 * Unix-domain UDP MQ client.
 */

#include <stdio.h>

#include "client.h"
#include "helpers.h"
#include "options.h"


static void print_usage(void);
static int run_client(struct options *);

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

    return run_client(&opts);
}

static void print_usage(void)
{
    static const char USAGE[] = "\n\
        client [ -hv ] [ -c config-file ] [ -s socket-file ] \n\
\n\
        -h, --help      Print a usage message and exit\n\
        -v, --verbose   Enable verbose output\n\
        -c FILE, --config-file FILE\n\
                        Read configuration from this file\n\
        -s FILE, --socket-file FILE\n\
                        Server socket file\n\
\n";

    puts(USAGE);

}

static int run_client(struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    return 0;
}

