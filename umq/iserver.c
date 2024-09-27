/*
 * Inet UDP server.
 */

#include <netinet/in.h>
#include <netinet/udp.h>
#include <sys/socket.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "iserver.h"
#include "message.h"
#include "options.h"

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
        printf("port = %d\n", opts.port);
    }

    return run_server(&opts);
}

static void print_usage(void)
{
    static const char USAGE[] =
            "\n\
        iserver [ -hv ] [ -c config-file ]\n\
\n\
        -h, --help      Print a usage message and exit\n\
        -v, --verbose   Enable verbose output\n\
        -p N, --port N\n\
                        Server socket port number\n\
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
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in sa = {0};
    sa.sin_family = AF_INET;
    sa.sin_port = htons(opts->port);
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

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
        struct sockaddr_in src = {0};
        socklen_t src_len = sizeof(struct sockaddr_in);

        ssize_t n = recvfrom(fd, rxbuf, RX_BUF_LEN, 0, (struct sockaddr *)&src,
                             &src_len);
        if (n < RX_BUF_LEN) {
            msg("Incomplete message (%ld/%ld)", n, RX_BUF_LEN);
            continue;
        }
        msg("recvfrom: src port %d, src addr %08X", ntohs(src.sin_port),
            ntohl(src.sin_addr.s_addr));
        struct message *m = (struct message *)rxbuf;
        msg("message -> %08X, %08X", m->message_id, m->request_id);
        switch (m->message_id) {
        case MSG_TEXT:
            printf("TEXT: %s\n", m->text);
            break;
        case MSG_U32: {
            unsigned int value = m->u32;
            printf("U32: %u\n", value);
            break;
        }
        case MSG_F32: {
            float value = m->f32;
            printf("F32: %f\n", value);
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

        int rs = socket(AF_INET, SOCK_DGRAM, 0);
        if (rs < 0) {
            perror("socket");
            continue;
        }

        struct sockaddr_in rsa = {0};
        rsa.sin_family = AF_INET;
        rsa.sin_port = htons(m->request_id);
        rsa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        socklen_t rsa_len = sizeof(struct sockaddr_in);

        struct message rsp = {0};
        rsp.message_id = MSG_STATUS;
        rsp.request_id = m->request_id;
        rsp.status = status;

        msg("sendto( status %d, port %d, addr %08X )", status,
            ntohs(rsa.sin_port), ntohl(rsa.sin_addr.s_addr));
        n = sendto(rs, &rsp, MSG_LEN, 0, (struct sockaddr *)&rsa, rsa_len);
        if (n != MSG_LEN) {
            perror("sendto");
        }

        err = close(rs);
        if (err < 0) {
            perror("close");
        }
    }

    msg("server offlne");

    if (close(fd) == -1) {
        perror("close");
    }

    msg("server exit");
    return 0;
}
