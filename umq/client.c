/*
 * Unix-domain UDP MQ client.
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
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
        -s FILE, --socket-file FILE\n\
                        Server socket file\n\
\n";

    puts(USAGE);
}

/**
 * Open a connection to the server's socket, open a response socket, send
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

    int request_id = randint(0, 0);
    request_id = ABS(request_id);
    msg("client's request id %d", request_id);

    /* Create client's response socket */
    msg("client socket");
    int cf = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (cf < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_un rsa = {0};
    rsa.sun_family = AF_LOCAL;
    snprintf(rsa.sun_path, 107, "/tmp/%08x.sock", request_id);
    (void)unlink(rsa.sun_path);
    int err = bind(cf, (struct sockaddr *)&rsa, sizeof(rsa));
    if (err < 0) {
        perror("bind");
        return -1;
    }

    /* Open server's socket */
    msg("server socket");
    int sf = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sf < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_un sa = {0};
    sa.sun_family = AF_UNIX;
    strncpy(sa.sun_path, opts->socket_file, strlen(opts->socket_file));

    err = connect(sf, (const struct sockaddr *)&sa, sizeof(sa));
    if (err < 0) {
        perror("connect");
        return -1;
    }

    char txbuf[MSG_LEN];
    struct message *txmsg = (struct message *)txbuf;

    /* Send message #1 */
    printf("message 1 = text\n");
    txmsg->message_id = MSG_TEXT;
    txmsg->request_id = request_id;
    strncpy(txmsg->text, "Green Lumber", 13);
    msg("sendto ( text '%s' )", txmsg->text);
    ssize_t n = sendto(sf, txbuf, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(cf);
        (void)close(sf);
        return -1;
    }

    /* Response #1 */
    msg("recvfrom");
    struct message rsp = {0};
    n = recvfrom(cf, &rsp, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 1 = %d\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    /* Send message #2 */
    printf("message 2 = U32\n");
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_U32;
    txmsg->request_id = request_id;
    txmsg->u32 = 3141592653U;
    msg("sendto ( u32 %u )", txmsg->u32);
    sendto(sf, txbuf, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(cf);
        (void)close(sf);
        return -1;
    }

    /* Response #2 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cf, &rsp, MSG_LEN, 0, NULL, 0);
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
    printf("message 3 = ?!?\n");
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_LAST + 123;
    txmsg->request_id = request_id;
    msg("sendto ( <bad msg> )");
    sendto(sf, txbuf, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(cf);
        (void)close(sf);
        return -1;
    }

    /* Response #3 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cf, &rsp, MSG_LEN, 0, NULL, 0);
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
    printf("message 4 = F32\n");
    memset(txbuf, 0, MSG_LEN);
    txmsg->message_id = MSG_F32;
    txmsg->request_id = request_id;
    txmsg->f32 = 2.718281;
    msg("sendto ( f32 %f )", txmsg->f32);
    sendto(sf, txbuf, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("sendto");
        (void)close(cf);
        (void)close(sf);
        return -1;
    }

    /* Response #4 */
    msg("recvfrom");
    memset(&rsp, 0, sizeof(rsp));
    n = recvfrom(cf, &rsp, MSG_LEN, 0, NULL, 0);
    if (n != MSG_LEN) {
        perror("recvfrom");
    }
    if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
        printf("response 4 = %d\n", rsp.status);
    } else {
        fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                rsp.message_id, rsp.request_id);
    }

    if (opts->quit) {
        /* Send message #5 */
        printf("message 5 = QUIT\n");
        txmsg->message_id = MSG_QUIT;
        txmsg->request_id = request_id;
        msg("sendto ( QUIT )");
        sendto(sf, txbuf, MSG_LEN, 0, NULL, 0);
        if (n != MSG_LEN) {
            perror("sendto");
        }

        msg("recvfrom");
        memset(&rsp, 0, sizeof(rsp));
        n = recvfrom(cf, &rsp, MSG_LEN, 0, NULL, 0);
        if (n != MSG_LEN) {
            perror("recvfrom");
        }
        if (rsp.message_id == MSG_STATUS && rsp.request_id == request_id) {
            printf("response 5 = %d\n", rsp.status);
        } else {
            fprintf(stderr, "Invalid response: message_id %d, request_id %d\n",
                    rsp.message_id, rsp.request_id);
        }
    }

    if (close(cf) == -1) {
        perror("close");
    }

    if (close(sf) == -1) {
        perror("close");
    }

    if (unlink(rsa.sun_path) == -1) {
        perror("unlink");
    }

    return 0;
}
