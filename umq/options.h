/**
 * Option processing for UMQ.
 */
#pragma once

#include <stdbool.h>

/** Default name of the server socket file. */
#define DEFAULT_SOCKET_FILE "/tmp/umq-server.sock"

/** Default server socket port number. */
#define DEFAULT_SERVER_PORT 2075

/**
 * Program runtime options.
 */
struct options {
    /** Print usage information and exit */
    bool help;
    /** Set log level to debug */
    bool verbose;
    /** Send a QUIT message (Client only) */
    bool quit;
    /** Server port */
    unsigned short port;
    /** Path of the server's socket file */
    const char *socket_file;
};

/**
 * Parse command line arguments.
 * @param argc The argument count from main.
 * @param argv The argument vector from main.
 * @param opts The options structure to initialize.
 * @retval  0 Success
 * @retval -1 Failure
 */
extern int init_options(int argc, char **argv, struct options *opts);
