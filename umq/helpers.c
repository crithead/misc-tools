/*
 * UMQ Helper functions.
 */

#include <stdarg.h>
#include <stdio.h>

#include "helpers.h"

static bool _messages_on = false;

void enable_messages(bool en)
{
    _messages_on = en;
}

void msg(const char *fmt, ...)
{
    static char line[LINESIZE];
    va_list args;

    if (!_messages_on)
    return;

    va_start(args, fmt);
    vsnprintf(line, LINESIZE, fmt, args);
    va_end(args);

    puts(line);
}

