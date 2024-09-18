/*
 * Miscellaneous functions.
 */

#pragma once

#include <stdbool.h>

#define LINESIZE 1024

extern void enable_messages(bool en);
extern void msg(const char *fmt, ...);
extern int randint(void);
