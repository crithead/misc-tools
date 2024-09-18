/*
 * UMQ Message
 */

#pragma once

enum {
    MSG_NONE = 0,
    MSG_QUIT,
    MSG_STATUS,
    MSG_TEXT,
    MSG_U32,
    MSG_F32,
    MSG_LAST
};

enum {
    STATUS_OK = 200,
    STATUS_BAD_REQUEST = 400,
    STATUS_FORBIDDEN = 403,
    STATUS_INTERNAL_SERVER_ERROR = 500,
    STATUS_NOT_IMPLEMENTED = 501,
    STATUS_UNKNOWN = 999
};

struct message {
    unsigned int message_id;
    unsigned int request_id;
    union {
        char text[24];
        float f32;
        unsigned int u32;
        int status;
    };
};

#define MSG_LEN sizeof(struct message)
