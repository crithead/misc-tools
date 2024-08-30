/*
 * UMQ Message
 */

#pragma once

enum {
    MSG_NONE = 0,
    MSG_QUIT,
    MSG_TEXT,
    MSG_U32,
    MSG_F32,
    MSG_LAST
};

struct message {
    unsigned int message_id;
    unsigned int request_id;
    union {
        char text[24];
        float f32;
        unsigned int u32;
    };
};

