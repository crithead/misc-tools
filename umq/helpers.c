/*
 * UMQ Helper functions.
 */

#include <limits.h>
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

    if (_messages_on) {
        va_start(args, fmt);
        vsnprintf(line, LINESIZE, fmt, args);
        va_end(args);
        puts(line);
    }
}

int randint(int a, int b)
{
    int value = 0;
    FILE *fp = fopen("/dev/random", "r");
    size_t n = fread(&value, sizeof(value), 1, fp);
    if (n < sizeof(value) && ferror(fp)) {
        fprintf(stderr, "fread");
    }
    (void)fclose(fp);

    if (a != 0 && b != 0) {
        if (a > b) {
            int t = a;
            a = b;
            b = t;
        }
        double f = (double)ABS(n) / (double)INT_MAX;
        value = a + (int)(f * (double)(b - a + 1));
    }

    return value;
}
