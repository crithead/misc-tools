/**
 * A program that passes a message from its input queue to its output queue
 * transforming it along the way.
 */

#include <ctype.h>
#include <getopt.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>

#define MSG_TXT_LEN 24
#define MSG_ID_QUIT (0xBAFFCEED)

static bool _messages_on = false;
static bool _relay_up = false;

static void enable_messages(bool en)
{
    _messages_on = en;
}

static void msg(const char *fmt, ...)
{
    if (_messages_on) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        putchar('\n');
    }
}

static void handle_signal(int sig)
{
    if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT) {
        if (_relay_up) {
            _relay_up = false;
        } else {
            exit(1);
        }
    } else if (sig == SIGUSR1) {
        /* TODO Rotate transform */
    }
}

enum {
    TF_NONE,
    TF_UPPER,
    TF_LOWER,

    TF_LAST
};

static const char *TFTAB[] = {"none", "upper", "lower"};

static int tf_enum(const char *s)
{
    for (int i = TF_NONE; i < TF_LAST; i++) {
        if (strncmp(s, TFTAB[i], 4) == 0) {
            return i;
        }
    }
    return TF_NONE;
}

static const char *tf_str(int tf)
{
    if (tf <= TF_NONE || tf >= TF_LAST) {
        return TFTAB[0];
    } else {
        return TFTAB[tf];
    }
}

struct options {
    bool help;
    bool verbose;
    int number;
    int transform;
    const char *input_file;
    const char *output_file;
};

struct message {
    int message_id;
    char text[MSG_TXT_LEN];
    int checksum;
};

#define MSG_LEN sizeof(struct message)

static int init_options(int argc, char **argv, struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    /* Set defaults */
    opts->help = false;
    opts->verbose = false;
    opts->number = -1;
    opts->transform = TF_NONE;
    opts->input_file = NULL;
    opts->output_file = NULL;

    static const char SHORT_OPTIONS[] = "hi:n:o:t:v";
    static struct option LONG_OPTIONS[] = {
            {"input-file", required_argument, 0, 'i'},
            {"output-file", required_argument, 0, 'o'},
            {"number", required_argument, 0, 'n'},
            {"transform", required_argument, 0, 't'},
            {"help", no_argument, 0, 'h'},
            {"verbose", no_argument, 0, 'v'},
            {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &option_index);

    while (c != -1) {
        switch (c) {
        case 'h':
            opts->help = true;
            break;
        case 'c':
            opts->input_file = optarg;
            break;
        case 'n':
            opts->number = atoi(optarg);
            break;
        case 'o':
            opts->output_file = optarg;
            break;
        case 't':
            opts->transform = tf_enum(optarg);
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

static int text_lower(char *txt, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        txt[i] = tolower(txt[i]);
    }
    return 0;
}

static int text_upper(char *txt, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        txt[i] = toupper(txt[i]);
    }
    return 0;
}

static void print_usage(void)
{
    static const char USAGE[] =
            "\n\
        server [ -hv ] [ -c config-file ]\n\
\n\
        -h, --help      Print a usage message and exit\n\
        -v, --verbose   Enable verbose output\n\
        -i FILE, --input-file FILE\n\
                        Input socket file\n\
        -o FILE, --output-file FILE\n\
                        Output socket file\n\
        -n N, --number N\n\
                        Number of message to send.\n\
        -t TRFM, --transform TRFM\n\
                        The transformation to perform.\n\
                        Options are: none, upper, lower\n\
\n\
        NUMBER: If N is not set, the program will relay messeges until it\n\
        receives a message with a QUIT ID, then it will exit. If N is set,\n\
        it will generate N messages, the Nth message will have the QUIT ID.\n\
        It will then exit.\n\
\n";

    puts(USAGE);
}

/**
 * Wait (forever) for the output socket file.
 * @param socket_file
 * @retval  0 Found it
 * @retval -1 Didn't find it
 */
static int wait_for_output(const char *socket_file)
{
    extern int nanosleep(const struct timespec *, struct timespec *);
    struct timespec ts = {0, 100000000}; /* 0.1 sec */

    while (true) {
        struct stat ss;
        int err = stat(socket_file, &ss);
        if (err == 0) {
            return 0;
        }

        nanosleep(&ts, NULL);
    }

    return -1;
}

static int calc_cksum(const char *buf, size_t len)
{
    (void)buf;
    (void)len;
    return 0x5A5A5A5A;
}

/* The "origin" creates new messages for output.  It reads input messages, but
 * prints them to the console instead of transforming and passing them.
 */
static int run_origin(struct options *opts)
{
    (void)opts;
    /* TODO */
    return -1;
}

static int run_relay(struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    int err = 0;

    msg("relay start");

    msg("input socket");
    int ifd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (ifd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_un isa = {0};
    isa.sun_family = AF_UNIX,
    strncpy(isa.sun_path, opts->input_file, strlen(opts->input_file));

    msg("input bind");
    err = bind(ifd, (struct sockaddr *)&isa, sizeof(isa));
    if (err != 0) {
        perror("bind");
        return -1;
    }

    err = wait_for_output(opts->output_file);
    if (err < 0) {
        msg("timed out waiting for output socket");
        return 2;
    }

    msg("output socket");
    int ofd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (ofd < 0) {
        perror("socket");
        return -1;
    }

    msg("output connect");
    struct sockaddr_un osa = {0};
    osa.sun_family = AF_UNIX,
    strncpy(osa.sun_path, opts->output_file, strlen(opts->output_file));
    err = connect(ofd, (struct sockaddr *)&osa, sizeof(osa));
    if (err < 0) {
        perror("connect");
        return -1;
    }

    msg("relay online");
    _relay_up = true;
    while (_relay_up) {
        char msgbuf[MSG_LEN];

        ssize_t n = recvfrom(ifd, msgbuf, MSG_LEN, 0, NULL, NULL);
        if (n != MSG_LEN) {
            msg("Incomplete message (%ld/%ld)", n, MSG_LEN);
            continue;
        }

        struct message *m = (struct message *)msgbuf;

        if (m->message_id == MSG_ID_QUIT) {
            _relay_up = false;
        }

        int cksum = calc_cksum(m->text, MSG_TXT_LEN);
        if (cksum != m->checksum) {
            msg("bad checksum");
            continue;
        }

        switch (opts->transform) {
        case TF_NONE:
            break;
        case TF_LOWER: {
            text_lower(m->text, MSG_TXT_LEN);
            break;
        }
        case TF_UPPER: {
            text_upper(m->text, MSG_TXT_LEN);
            break;
        }
        default:
            printf("Msg ID = %d\n", m->message_id);
            break;
        }

        /* TODO Send message to output_file */
    }

    msg("relay offlne");

    if (close(ifd) == -1) {
        perror("close");
    }
    if (close(ofd) == -1) {
        perror("close");
    }
    if (unlink(opts->input_file) == -1) {
        perror("unlink");
    }

    msg("relay exit");
    return 0;
}

int main(int argc, char **argv)
{
    struct options opts = {0};
    init_options(argc, argv, &opts);

    if (opts.help) {
        print_usage();
        return 0;
    }

    if (opts.verbose) {
        enable_messages(true);
        printf("input_file = %s\n", opts.input_file);
        printf("output_file = %s\n", opts.output_file);
        printf("transform = %s\n", tf_str(opts.transform));
    }

    if (signal(SIGINT, handle_signal) < 0) {
        perror("signal");
        return 1;
    }
    if (signal(SIGTERM, handle_signal) < 0) {
        perror("signal");
        return 1;
    }
    if (signal(SIGQUIT, handle_signal) < 0) {
        perror("signal");
        return 1;
    }

    if (opts.number == -1) {
        return run_relay(&opts);
    } else {
        return run_origin(&opts);
    }
}
