/*
 * Inet UDP client.
 */

#include <netinet/in.h>
#include <netinet/udp.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "helpers.h"
#include "message.h"
#include "options.h"

static void print_usage(void);
static int run_client(struct options *);

/**
 * Main
 */
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

/**
 * Print helpful usage information.
 */
static void print_usage(void)
{
    static const char USAGE[] =
            "\n\
        client [ -hqv ] [ -s socket-file ] [ --help ] [ --quit ]\n\
\n\
        -h, --help      Print a usage message and exit\n\
        -q, --quit      Send a quit message\n\
        -v, --verbose   Enable verbose output\n\
        -p N, --port N\n\
                        Server socket port\n\
\n";

    puts(USAGE);
}

/**
 * Open a conneciton to the server's socket, open a response socket, send
 * a request to the server, receive a response from the server.
 * @param opts Program options
 * @retval  0 Ok
 * @retval -1 Not Ok
 */
static int run_client(struct options *opts)
{
    if (opts == NULL) {
        return -1;
    }

    /* Request ID is client's response port number. */
    int request_id = randint(opts->port + 100, opts->port + 1000);
    msg("client's request id %d", request_id);

    /* Create client's response socket */
    msg("client socket");
    int cs = socket(AF_INET, SOCK_DGRAM, 0);
    if (cs < 0) {
        perror("socket");
        return -1;
    }

    socklen_t rsa_len = sizeof(struct sockaddr_in);
    struct sockaddr_in rsa = {0};
    rsa.sin_family = AF_INET;
    rsa.sin_port = htons(request_id);
    rsa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    msg("client bind");
    int err = bind(cs, (struct sockaddr *)&rsa, rsa_len);
    if (err != 0) {
        perror("bind");
        return -1;
    }

    /* Open server socket */
    msg("server socket");
    int ss = socket(AF_INET, SOCK_DGRAM, 0);
    if (ss < 0) {
        perror("socket");
        return -1;
    }

    size_t ssa_len = sizeof(struct sockaddr_in);
    struct sockaddr_in ssa;
    ssa.sin_family = AF_INET;
    ssa.sin_port = htons(opts->port);
    ssa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    char txbuf[MSG_LEN] = {0};
    struct message *txmsg = (struct message *)txbuf;

    /* Send message #1 */
    txmsg->message_id = MSG_TEXT;
    txmsg->request_id = request_id;
    strncpy(txmsg->text, "Green Lumber", 13);
    printf("message 1 (%s)\n", txmsg->text);

    msg("sendto ( text '%s', port %d, addr %08X )", txmsg->text,
        ntohs(ssa.sin_port), ntohl(ssa.sin_addr.s_addr));
    ssize_t n = sendto(ss, txbuf, MSG_LEN, 0, (struct sockaddr *)&ssa, ssa_len);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(ss);
        return -1;
    }

    /* Response #1 */
    struct sockaddr_in src = {0};
    socklen_t src_len = sizeof(struct sockaddr_in);

    msg("recvfrom");
    struct message rsp = {0};
    n = recvfrom(cs, &rsp, MSG_LEN, 0, (struct sockaddr *)&src, &src_len);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 1 (%d)\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    /* Send message #2 */
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_U32;
    txmsg->request_id = request_id;
    txmsg->u32 = 3141592653U;
    printf("message 2 (%u)\n", txmsg->u32);

    msg("sendto ( U32 '%d', port %d, addr %08X )", txmsg->u32,
        ntohs(ssa.sin_port), ntohl(ssa.sin_addr.s_addr));
    sendto(ss, txbuf, MSG_LEN, 0, (struct sockaddr *)&ssa, ssa_len);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(ss);
        (void)close(cs);
        return -1;
    }

    /* Response #2 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cs, &rsp, MSG_LEN, 0, (struct sockaddr *)&rsa, &rsa_len);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 2 = %d\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    /* Send message #3 */
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_LAST + 123;
    txmsg->request_id = request_id;
    printf("message 3 (?!?)\n");

    msg("sendto ( <BAD MSG> , port %d, addr %08X )", ntohs(ssa.sin_port),
        ntohl(ssa.sin_addr.s_addr));
    sendto(ss, txbuf, MSG_LEN, 0, (struct sockaddr *)&ssa, ssa_len);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(ss);
        (void)close(cs);
        return -1;
    }

    /* Response #3 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cs, &rsp, MSG_LEN, 0, (struct sockaddr *)&rsa, &rsa_len);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 3 = %d\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    /* Send message #4 */
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_F32;
    txmsg->request_id = request_id;
    txmsg->f32 = 2.718281;
    printf("message 4 (%f)\n", txmsg->f32);

    msg("sendto ( f32 %f, port %d, addr %08X )", txmsg->f32,
        ntohs(ssa.sin_port), ntohl(ssa.sin_addr.s_addr));
    sendto(ss, txbuf, MSG_LEN, 0, (struct sockaddr *)&ssa, ssa_len);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(ss);
        (void)close(cs);
        return -1;
    }

    /* Response #4 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cs, &rsp, MSG_LEN, 0, (struct sockaddr *)&rsa, &rsa_len);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 4 (%d)\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    if (opts->quit) {
        /* Send message #5 */
        txmsg->message_id = MSG_QUIT;
        txmsg->request_id = request_id;
        printf("message 5 (QUIT)\n");

        msg("sendto ( QUIT, port %d, addr %08X )", ntohs(ssa.sin_port),
            ntohl(ssa.sin_addr.s_addr));
        sendto(ss, txbuf, MSG_LEN, 0, (struct sockaddr *)&ssa, ssa_len);
        if (n != MSG_LEN) {
            perror("sendto");
        }

        msg("recvfrom");
        memset(&rsp, 0, sizeof(rsp));
        n = recvfrom(cs, &rsp, MSG_LEN, 0, (struct sockaddr *)&src, &src_len);
        if (n != MSG_LEN) {
            perror("recvfrom");
        }
        if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
            printf("response 5 (%d)\n", rsp.status);
        } else {
            fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                    rsp.message_id, rsp.request_id);
        }
    }

    if (close(cs) < 0) {
        perror("close");
    }

    if (close(ss) < 0) {
        perror("close");
    }

    return 0;
}
