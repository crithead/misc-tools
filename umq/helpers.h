#pragma once

#include <stdbool.h>

#define LINESIZE 1024

extern void msg(const char *fmt, ...);
extern void enable_messages(bool en);

