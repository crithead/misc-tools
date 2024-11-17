//
//
//

#include <getopt.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>

#include "helpers.h"

#if !defined(PATH_MAX)
#define PATH_MAX 1024
#endif

extern char *realpath(const char *restrict path,
                      char *restrict resolved_path);

/*
 * Get the device file for a partition UUID.
 * uuid - The device's UUID
 * device_file - Output buffer 
 * len - Length of output buffer
 * Return:  0 Success, -1 Failure
 */
int device_file_from_uuid(const char *uuid, char *device_file, size_t len)
{
    char path[PATH_MAX] = {0};

    (void)strncpy(path, "/dev/disk/by-uuid/", PATH_MAX - 1);
    (void)strncat(path, uuid, PATH_MAX - 1);

    struct stat ss = {0};
    if (stat(path, &ss) == -1) {
        perror("stat");
        return -1;
    }

    char *p = realpath((const char *)path, device_file);

    return (p == NULL) ? -1 : 0 ;
}


int init_options(int argc, char **argv, struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    /* Set defaults */
    opts->help = false;
    opts->verbose = false;
    opts->device_file = NULL;
    opts->mount_dir = NULL;

    static const char SHORT_OPTIONS[] = "d:hm:v";
    static struct option LONG_OPTIONS[] = {
        {"device_file", required_argument,  0,  'd' },
        {"mount_dir",   required_argument,  0,  'm' },
        {"help",        no_argument,        0,  'h' },
        {"verbose",     no_argument,        0,  'v' },
        {0,             0,                  0,   0 }
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &option_index);

    while (c != -1) {
        switch (c) {
        case 'd':
            opts->device_file = optarg;
            break;
        case 'm':
            opts->mount_dir = optarg;
            break;
        case 'h':
            opts->help = true;
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

void print_usage(void)
{
    const char USAGE[] = "\n\
    mounter -- mount a device on a directory\n\
\n\
    mounter [ -h | --help ] [ -v | --verbose ]\n\
            -d DEVFILE | --device_file DEVFILE\n\
            -m MNTDIR | --mount_dir MNTDIR\n\
\n";
    puts(USAGE);
}

bool _messages_on = false;

void info(const char *fmt, ...)
{
    va_list args;

    if (_messages_on) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

void warn(const char *fmt, ...)
{
    va_list args;

    if (_messages_on) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

