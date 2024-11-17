/**
 *
 */

#include "helpers.h"

static int mount(struct options *);
static int unmount(struct options *);

int main(int argc, char **argv)
{
    struct options opts = {0};
    init_options(argc, argv, &opts);

    if (opts.help) {
        print_usage();
        return 0;
    }

    if (opts.verbose) {
        extern bool _messages_on;
        _messages_on = true;
    }

    if (opts.device_file == NULL && opts.mount_dir == NULL) {
        print_usage();
        return 1;
    }

    if (opts.device_file != NULL && opts.mount_dir != NULL) {
        return mount(&opts);
    }

    if (opts.device_file == NULL && opts.mount_dir != NULL) {
        return unmount(&opts);
    }

    return 1;
}

static int mount(struct options *opts)
{
    return 1;
}

static int unmount(struct options *opts)
{
    return 1;
}

