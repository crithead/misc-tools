//
//
#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * Program runtime options.
 */
struct options {
    /** Print usage information and exit. */
    bool help;
    /** Set log level to debug. */
    bool verbose;
    /** The device file */
    const char *device_file;
    /** Directory on which to mount file system */
    const char *mount_dir;
};

/**
 * Get the device file for a partition UUID.
 * @param[in] uuid The device's UUID
 * @param[out] device_file Output buffer 
 * @param[in] len Length of output buffer
 * @retval  0 Success
 * @retval -1 Failure
 */
extern int device_file_from_uuid(const char *uuid, char *device_file, size_t len);

extern int init_options(int argc, char **argv, struct options *opts);
extern void info(const char *fmt, ...);
extern void warn(const char *fmt, ...);
extern void print_usage(void);
