/**
 * Capability Lister
 *
 */

#include <linux/capability.h>
#include <sys/prctl.h>

#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINELEN (128)

static const char USAGE[] = "\
\n\
    capalist -- list capabilities of this process (and more)\n\
\n\
OPTIONS\n\
    -h, --help      Print usage and exit\n\
    -v, --verbose   Enable extra messages\n\
\n";

enum has_cap {
    HAS_CAP_UNKNOWN,
    HAS_CAP_NO,
    HAS_CAP_YES
};

/**
 * Capability Info.
 */
struct capability_item {
    const char *name;
    const int cap_id;
    int has_cap_ambient;
    int has_cap_bounding;
    int has_cap_inheritable;
    int has_cap_effective;
    int has_cap_permitted;
};

/** Program options. */
struct options {
    bool verbose;
    bool print_usage;
};

/** Message enable flag. */
static bool _messages_on = false;

static struct capability_item caps[] = {
    { "CAP_CHOWN", CAP_CHOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_DAC_OVERRIDE", CAP_DAC_OVERRIDE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_DAC_READ_SEARCH", CAP_DAC_READ_SEARCH, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_FOWNER", CAP_FOWNER, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_FSETID", CAP_FSETID, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_KILL", CAP_KILL, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SETGID", CAP_SETGID, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SETUID", CAP_SETUID, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SETPCAP", CAP_SETPCAP, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_LINUX_IMMUTABLE", CAP_LINUX_IMMUTABLE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_NET_BIND_SERVICE", CAP_NET_BIND_SERVICE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_NET_BROADCAST", CAP_NET_BROADCAST, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_NET_ADMIN", CAP_NET_ADMIN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_NET_RAW", CAP_NET_RAW, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_IPC_LOCK", CAP_IPC_LOCK, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_IPC_OWNER", CAP_IPC_OWNER, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_MODULE", CAP_SYS_MODULE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_RAWIO", CAP_SYS_RAWIO, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_CHROOT", CAP_SYS_CHROOT, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_PTRACE", CAP_SYS_PTRACE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_PACCT", CAP_SYS_PACCT, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_ADMIN", CAP_SYS_ADMIN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_BOOT", CAP_SYS_BOOT, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_NICE", CAP_SYS_NICE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_RESOURCE", CAP_SYS_RESOURCE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_TIME", CAP_SYS_TIME, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYS_TTY_CONFIG", CAP_SYS_TTY_CONFIG, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_MKNOD", CAP_MKNOD, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_LEASE", CAP_LEASE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_AUDIT_WRITE", CAP_AUDIT_WRITE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_AUDIT_CONTROL", CAP_AUDIT_CONTROL, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SETFCAP", CAP_SETFCAP, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_MAC_OVERRIDE", CAP_MAC_OVERRIDE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_MAC_ADMIN", CAP_MAC_ADMIN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_SYSLOG", CAP_SYSLOG, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_WAKE_ALARM", CAP_WAKE_ALARM, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_BLOCK_SUSPEND", CAP_BLOCK_SUSPEND, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_AUDIT_READ", CAP_AUDIT_READ, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_PERFMON", CAP_PERFMON, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_BPF", CAP_BPF, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    { "CAP_CHECKPOINT_RESTORE", CAP_CHECKPOINT_RESTORE, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN },
    /* { "CAP_LAST_CAP", CAP_LAST_CAP, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN }, */
    { NULL, -1, HAS_CAP_UNKNOWN, HAS_CAP_UNKNOWN }
};

static void enable_messages(bool enable);
static void get_options(int argc, char **argv, struct options *opts);
static const char *has_cap_str(int has_cap);
static void init_cap_table(void);
static void msg(const char *fmt, ...);
static void print_cap_table(void);
static void print_usage(void);

/**
 * Do Stuff
 * @param[in] argc Argument count
 * @param[in] argv Argument vector
 */
int main(int argc, char **argv)
{
    struct options opts = { 0 };
    get_options(argc, argv, &opts);

    if (opts.print_usage) {
        print_usage();
        return 0;
    }

    if (opts.verbose) {
        enable_messages(true);
    }

    msg("--- Initialize capability table");
    init_cap_table();

    msg("--- Print capability table");
    print_cap_table();

    msg("--- Done");

    return EXIT_SUCCESS;
}

/**
 * Enable extra messages.
 * @param[in] enable Turn messages on or off.
 */
static void enable_messages(bool enable)
{
    _messages_on = enable;
}

/**
 * Parse the command line arguments into an options structure.
 * @param[in] argc Argument count
 * @param[in] argv Argument vector
 * @param[out] opts Poiter to an options structure
 */
static void get_options(int argc, char **argv, struct options *opts)
{
    int c;

    if (opts == NULL) {
        return;
    }

    /* set options defaults */
    opts->print_usage = false;
    opts->verbose = false;

    while (true) {
        int option_index = 0;
        static struct option long_options[] = {
            { "help", no_argument, 0, 'h' },
            { "verbose", no_argument, 0, 'v' },
            { 0, 0, 0, 0, }
        };

        c = getopt_long(argc, argv, "hv", long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'h':
            opts->print_usage = true;
            break;
        case 'v':
            opts->verbose = true;
            break;
        default:
            break;
        }
    }
}

/**
 * Print a message to the console, if messages enabled.
 * @param[in] fmt Print format
 * @param ... argument list
 */
static void msg(const char *fmt, ...)
{
    static char line[LINELEN] = {0};
    if (_messages_on) {
        va_list a;
        va_start(a, fmt);
        int n = vsnprintf(line, LINELEN, fmt, a);
        va_end(a);
        if (n >= LINELEN) {
            fprintf(stderr, "%s: Warning: line overflow", __func__);
            line[LINELEN - 1] = '\0';
        } else {
            line[n] = '\0';
        }
        puts(line);
    }
}

/**
 * Return a pointer to a string corresponding to HAS_CAP values.
 * @param[in] has_cap A HAS_CAP enumerated value
 * @return Corresponding HAS_CAP string
 */
static const char *has_cap_str(int has_cap)
{
    switch (has_cap) {
    case HAS_CAP_YES:
        return "Yes";
    case HAS_CAP_NO:
        return "No";
    default:
        return "Unknown";
    }
}

/**
 * Initialize the caps table.
 * @note This function sets `has_cap` in the global caps table.
 * @retval 0 Success
 * @retval 1 Failure
 */
static void init_cap_table(void)
{
    /* Read all capabilities */
    for (int i = 0; caps[i].cap_id >= 0; i++) {
        int value = prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, caps[i].cap_id, 0, 0);
        switch (value) {
        case 1:
            caps[i].has_cap_ambient = HAS_CAP_YES;
            break;
        case 0:
            caps[i].has_cap_ambient = HAS_CAP_NO;
            break;
        default:
            msg("PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, %s -> %d", caps[i].name, value);
            break;
        }

        value = prctl(PR_CAPBSET_READ, caps[i].cap_id, 0, 0, 0);
        switch (value) {
        case 1:
            caps[i].has_cap_bounding = HAS_CAP_YES;
            break;
        case 0:
            caps[i].has_cap_bounding = HAS_CAP_NO;
            break;
        default:
            msg("PR_CAPBSET_READ, %s -> %d", caps[i].name, value);
            break;
        }
    }
}

/*
    TODO - figure out how to get the values with libcap(3) functions

struct __user_cap_header_struct header;
struct __user_cap_data_struct data;

header.version = LINUX_CAPABILITY_VERSION_3;
header.pid = getpid();

data.inheritable |= CAP_TO_MASK(CAP_*);
data.effective |= CAP_TO_MASK(CAP_*);
data.permitted |= CAP_TO_MASK(CAP_*);

capset(&header, &data);

*/




/**
 * Print the global cap table.
 */
static void print_cap_table(void)
{
    printf("\t%-24s %s %s\n", "Capability", "Ambient", "Bound");
    for (int i = 0; caps[i].cap_id >= 0; i++) {
        printf("\t%-24s %4s    %4s\n", caps[i].name,
               has_cap_str(caps[i].has_cap_ambient),
               has_cap_str(caps[i].has_cap_bounding));
    }
}

/**
 * Print a helpful usage message.
 */
static void print_usage(void)
{
    puts(USAGE);
}

