/**
 * A generic Linux New Style daemon.
 *
 * Features:
 * - SIGTERM: exit cleanly
 * - SIGHUP - reload configo
 * - Call sd_notify(3) appropriately
 */

#include <systemd/sd-daemon.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include "log.h"
#include "message.h"
#include "options.h"
#include "service.h"

#define PID_FILE "/run/templated.pid"

/** Current requested service */
enum {
    /** None */
    SVC_NONE,
    /** Reload configuration */
    SVC_RELOAD,
    /** Print service statistics to log */
    SVC_STATS,
    /** Stop the service */
    SVC_STOP
};

static void dump_stats(void);
static void print_usage(void);
static void reload(void);
static void signal_handler(int);
static void write_pid_file(const char *);
static void remove_pid_file(const char *);

static int current_request = SVC_NONE;

/**
 * Perform a service.
 * - Daemonize
 * - Install signal handlers
 * - Provide "service"
 * @param argc Argument count
 * @param argv Argument vector
 * @retval 0 No errors
 * @retval 1 Errors
 */
int main( int argc, char **argv)
{
    struct options opts;
    init_options(argc, argv, &opts);

    if (opts.help) {
        print_usage();
        return 0;
    }

    openlog("SVC", LOG_PID, LOG_USER);


    write_pid_file(PID_FILE);


    /* Install SIG handlers for INT, TERM, USR1, USR2 */
    struct sigaction sigact = {0};
    sigact.sa_handler = signal_handler;
    sigact.sa_flags = 0;

    if (sigaction(SIGTERM, &sigact, NULL) < 0) {
        emergency("Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        emergency("Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGHUP, &sigact, NULL) < 0) {
        emergency("Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGUSR1, &sigact, NULL) < 0) {
        emergency("Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGUSR2, &sigact, NULL) < 0) {
        emergency("Sigaction: %s", strerror(errno));
        return 1;
    }

    sd_notify(0, "READY=1");
    notice("Online");

    /* Perform a "service" */
    int service_up = true;
    current_request = SVC_NONE;
    while (service_up) {
        int value = pause();
        if (value < 0) {
            switch (current_request) {
                case SVC_RELOAD:
                    sd_notify(0, "RELOADING=1");
                    reload();
                    sd_notify(0, "READY=1");
                    break;
                case SVC_STATS:
                    dump_stats();
                    break;
                case SVC_STOP:
                    service_up = false;
                    sd_notify(0, "STOPPING=1");
                    debug("Received SIGINT, shutting down");
                    break;
                default:
                    break;
            }
        } else {
            debug("pause returned %d", value);
        }
    }

    remove_pid_file(PID_FILE);
    notice("Offline");
    sd_notify(0, "EXIT_STATUS=0");

    return 0;
}

/**
 * Write "service" statistics to the log.
 */
static void dump_stats(void)
{
    syslog(LOG_INFO, "Stats");
}

static void print_usage(void)
{
    static const char USAGE[] = "\n\
    templated [ -hqv ] [ -c FILE ] [ --config-file FILE ] [ --help ]\n\
        [ --quiet ] [ --verbose ]\n\
\n\
    OPTIONS\n\
    -h, --help      Print usage message and exit\n\
    -q, --quiet     Only log warnings and above\n\
    -v, --verbose   Log everything (Debug and above)\n\
\n\
    SIGNALS\n\
    USR1    Dump stats to log\n\
    USR2    Same as USR1\n\
    HUP     Reload configuration file\n\
    INT     Shutdown\n\
\n";

    puts(USAGE);
}

/**
 * Reload the configuration.
 */
static void reload(void)
{
    syslog(LOG_NOTICE, "Reload");
}

/**
 * Signal handler
 * @param sig The signal that invoked this function
 * @retval 0 Always
 */
static void signal_handler(int sig)
{
    switch (sig) {
        case SIGINT:
            current_request = SVC_STOP;
            break;
        case SIGUSR1:
            current_request = SVC_RELOAD;
            break;
        case SIGUSR2:
            current_request = SVC_STATS;
            break;
        default:
            syslog(LOG_DEBUG, "Unhandled signal: %d", sig);
            break;
    }
}

/**
 * Remove this process's PID file.
 * @param pid_file The path of the PID file.
 */
static void remove_pid_file(const char *pid_file)
{
    if (unlink(pid_file) < 0) {
        syslog(LOG_ERR, "Failed to unlink PID file (%s): %s", pid_file, strerror(errno));
    } else {
        syslog(LOG_DEBUG, "Unlinked PID file (%s)", pid_file);
    }
}

/**
 * Write this process's PID to a file.
 * @param pid_file The path of the file in which the PID is to be written.
 */
static void write_pid_file(const char *pid_file)
{
    pid_t pid = getpid();
    FILE *fp = fopen(pid_file, "w");
    if (fp != NULL) {
        fprintf(fp, "%d", pid);
        fclose(fp);
        syslog(LOG_DEBUG, "PID FILE = %s", pid_file);
    } else {
        syslog(LOG_ERR, "Failed to write PID file: %s", strerror(errno));
    }
}

