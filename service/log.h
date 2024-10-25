/**
 * Logging templated.
 */
#pragma once

/**
 * Print a message at DEBUG level.
 * @param[in] lvl  Log level
 */
extern void set_log_level(int lvl);

extern void debug(const char *fmt, ...);

/**
 * Print a message at NOTICE level.
 * @param[in] fmt Format string
 */
extern void notice(const char *fmt, ...);

/**
 * Print a message at EMERGENCY level.
 * @param[in] fmt Format string
 */
extern void emergency(const char *fmt, ...);


