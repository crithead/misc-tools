/*
 * Unix-domain UDP server.
 */

#include <sys/socket.h>
#include <sys/un.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "message.h"
#include "options.h"
#include "server.h"

#define RX_BUF_LEN sizeof(struct message)

static void print_usage(void);
static int run_server(struct options *);

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
        printf("socket_file = %s\n", opts.socket_file);
    }

    return run_server(&opts);
}

static void print_usage(void)
{
    static const char USAGE[] =
            "\n\
        server [ -hv ] [ -c config-file ]\n\
\n\
        -h, --help      Print a usage message and exit\n\
        -v, --verbose   Enable verbose output\n\
        -s FILE, --socket-file FILE\n\
                        Server socket file\n\
\n";

    puts(USAGE);
    printf("Version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
}

static int run_server(struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }
    msg("server start");

    msg("socket");
    int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_un sa = {0};
    sa.sun_family = AF_LOCAL,
    strncpy(sa.sun_path, opts->socket_file, strlen(opts->socket_file));
    (void)unlink(sa.sun_path);

    msg("bind");
    int err = bind(fd, (struct sockaddr *)&sa, sizeof(sa));
    if (err != 0) {
        perror("bind");
        return -1;
    }

    msg("server online");
    bool server_up = true;
    while (server_up) {
        int status = STATUS_OK;
        char rxbuf[RX_BUF_LEN];
        ssize_t n = recvfrom(fd, rxbuf, RX_BUF_LEN, 0, NULL, NULL);
        if (n < RX_BUF_LEN) {
            msg("Incomplete message (%ld/%ld)", n, RX_BUF_LEN);
            continue;
        }
        struct message *m = (struct message *)rxbuf;
        msg("message -> %08X, %08X", m->message_id, m->request_id);
        switch (m->message_id) {
        case MSG_TEXT:
            printf("%s\n", m->text);
            break;
        case MSG_U32: {
            unsigned int value = m->u32;
            printf("%u\n", value);
            break;
        }
        case MSG_F32: {
            float value = m->f32;
            printf("%f\n", value);
            break;
        }
        case MSG_QUIT:
            server_up = false;
            break;
        default:
            status = STATUS_BAD_REQUEST;
            printf("Bad Msg %d\n", m->message_id);
            break;
        }

        int rd = socket(AF_LOCAL, SOCK_DGRAM, 0);
        if (rd < 0) {
            perror("socket");
            continue;
        }

        struct sockaddr_un rsa = {0};
        rsa.sun_family = AF_LOCAL,
        snprintf(rsa.sun_path, 107, "/tmp/%08x.sock", m->request_id);

        err = connect(rd, (struct sockaddr *)&rsa, sizeof(rsa));
        if (err < 0) {
            perror("connect");
            close(rd);
            continue;
        }

        struct message rsp = {0};
        rsp.message_id = MSG_STATUS;
        rsp.request_id = m->request_id;
        rsp.status = status;

        n = sendto(rd, &rsp, MSG_LEN, 0, NULL, 0);
        if (n != MSG_LEN) {
            perror("sendto");
        }

        err = close(rd);
        if (err < 0) {
            perror("close");
        }
    }

    msg("server offlne");

    if (close(fd) == -1) {
        perror("close");
    }
    if (unlink(opts->socket_file) == -1) {
        perror("unlink");
    }

    msg("server exit");
    return 0;
}
