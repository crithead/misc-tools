/*
 * Logging helpers for templated.
 */

#include <stddef.h>

#include "log.h"

#define LINELEN 128

static int _log_level = LOG_NOTICE;
static char _log_line[LINELEN];

void set_log_level(int lvl)
{
    if (lvl < LOG_EMERG) {
        _log_level = LOG_EMERG;
    } else if (lvl > LOG_DEBUG) {
        _log_level = LOG_DEBUG;
    } else {
        _log_level = lvl;
    }
}

void debug(const char *fmt, ...)
{
    if (fmt == NULL || _log_level > LOG_DEBUG) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    memset(_log_line, 0, LINELEN);
    size_t n = snprintf(_log_line, LINELEN, "<%d> %s", LOG_DEBUG, fmt);
    svnprintf(_log_line + n, LINELEN, _log_line, args);
    va_end(args);
    fprintf(stderr, _log_line);
}
void notice(const char *fmt, ...)
{
    if (fmt == NULL || _log_level > LOG_NOTICE) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    memset(_log_line, 0, LINELEN);
    size_t n = snprintf(_log_line, LINELEN, "<%d> %s", LOG_DEBUG, fmt);
    svnprintf(_log_line + n, LINELEN, _log_line, args);
    va_end(args);
    fprintf(stderr, _log_line);
}

void emergency(const char *fmt, ...)
{
    if (fmt == NULL || _log_level > LOG_EMERG) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    memset(_log_line, 0, LINELEN);
    size_t n = snprintf(_log_line, LINELEN, "<%d> %s", LOG_EMERG, fmt);
    svnprintf(_log_line + n, LINELEN, _log_line, args);
    va_end(args);
    fprintf(stderr, _log_line);
}
