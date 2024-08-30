/*
 * Unix-domain UDP MQ client.
 */

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "helpers.h"
#include "message.h"
#include "options.h"

#define TX_BUF_LEN sizeof(struct message)

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

    msg("socket");
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_un sa;
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, opts->socket_file, strlen(opts->socket_file));

    int err = connect(fd, (const struct sockaddr *)&sa, sizeof(sa));
    if (err < 0) {
        perror("connect");
        return -1;
    }

    char txbuf[TX_BUF_LEN];
    struct message *txmsg = (struct message *)txbuf;

    txmsg->message_id = MSG_TEXT;
    txmsg->request_id = 991U;
    strncpy(txmsg->text, "Hello", 6);
    sendto(fd, txbuf, TX_BUF_LEN, 0, NULL, 0);

    txmsg->message_id = MSG_U32;
    txmsg->request_id = 992U;
    txmsg->u32 = 3141592653U;
    sendto(fd, txbuf, TX_BUF_LEN, 0, NULL, 0);

    txmsg->message_id = MSG_F32;
    txmsg->request_id = 993U;
    txmsg->f32 = 2.718281;
    sendto(fd, txbuf, TX_BUF_LEN, 0, NULL, 0);

    txmsg->message_id = MSG_QUIT;
    txmsg->request_id = 999U;
    sendto(fd, txbuf, TX_BUF_LEN, 0, NULL, 0);

    if (close(fd) < 0) {
        perror("close");
    }

    return 0;
}

