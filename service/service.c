/**
 * A generic service.
 */

/* Required for daemon(3) */
#define _DEFAULT_SOURCE

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

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
static void reload(void);
static void signal_handler(int);
static void write_pid(const char *);

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
    /* Daemonize */
    if (daemon(0, 0) < 0) {
        openlog("SVC", LOG_PID, LOG_USER);
        syslog(LOG_CRIT, "Daemonization failed: %s", strerror(errno));
        closelog();
        return 1;
    }

    write_pid(PID_FILE);

    openlog("SVC", LOG_PID, LOG_USER);

    /* Install SIG handlers for INT, USR1, USR1 */
#if 0
    struct sigaction sigact = {
        .sa_handler = signal_handler,
        .sa_sigaction = NULL,
        .sa_mask = 0,
        .sa_flags = 0
    };
#else
    struct sigaction sigact = {0};
    sigact.sa_handler = signal_handler;
    sigact.sa_flags = 0;
#endif

    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        syslog(LOG_CRIT, "Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGUSR1, &sigact, NULL) < 0) {
        syslog(LOG_CRIT, "Sigaction: %s", strerror(errno));
        return 1;
    }

    if (sigaction(SIGUSR2, &sigact, NULL) < 0) {
        syslog(LOG_CRIT, "Sigaction: %s", strerror(errno));
        return 1;
    }

    syslog(LOG_NOTICE, "Online");

    /* Perform a "service" */
    int service_up = true;
    current_request = SVC_NONE;
    while (service_up) {
        int value = pause();
        if (value < 0) {
            switch (current_request) {
                case SVC_RELOAD:
                    reload();
                    break;
                case SVC_STATS:
                    dump_stats();
                    break;
                case SVC_STOP:
                    service_up = false;
                    syslog(LOG_DEBUG, "Received SIGINT, shutting down");
                    break;
                default:
                    break;
            }
        } else {
            syslog(LOG_DEBUG, "pause returned %d", value);
        }
    }

    syslog(LOG_NOTICE, "Offline");
    closelog();

    return 0;
}

/**
 * Write "service" statistics to the log.
 */
static void dump_stats(void)
{
    syslog(LOG_INFO, "Stats");
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
 * Write this process's PID to a file.
 * @param pid_file The path of the file in which the PID is to be written.
 */
static void write_pid_file(const char *pid_file)
{
    pid_t pid = getpid();
    int fd = open(pid_file, O_CREAT | O_WRONLY | O_TRUNC,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd > 0) {
        fprintf(fd, "%d", pid);
        close(fd);
        syslog(LOG_DEBUG, "PID FILE = %s", pid_file);
    } else {
        syslog(LOG_ERR, "Failed to write PID file");
    }
}

