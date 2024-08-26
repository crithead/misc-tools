/**
 * Message handling for templated.
 */
#pragma once

struct request {
    char id;
    char sn;
};

struct response {
    char id;
    char sn;
    char data[14];
};

/**
 * Get the next message.
 * @param msg[out] Message buffer
 * @retval  0 Success
 * @retval -1 Failure
 */
extern int next_message(struct request *msg);

/**
 * Send a response message.
 * @param msg[in] Message buffer
 * @retval  0 Success
 * @retval -1 Failure
 */
extern int send_message(struct response *msg);

