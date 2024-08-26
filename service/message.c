/*
 * Message handling implementation for templated.
 */

#include <stddef.h>
#include <syslog.h>

#include "message.h"

/*
 * Get the next message.
 * @param msg[out] Message buffer
 * @retval  0 Success
 * @retval -1 Failure
 */
int next_message(struct request *msg)
{
    if (msg == NULL) {
        return -1;
    }

    return 0;
}

/**
 * Send a response message.
 * @param msg[in] Message buffer
 * @retval  0 Success
 * @retval -1 Failure
 */
int send_message(struct response *msg)
{
    if (msg == NULL) {
        return -1;
    }

    return 0;
}

