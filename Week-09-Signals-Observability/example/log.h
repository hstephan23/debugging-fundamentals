/*
 * log.h — a tiny structured-logging header.
 *
 * Every line has: time, level, file:line, then key=value pairs.
 * One event per line. grep/awk-friendly. No prose.
 *
 * Usage:
 *   LOG_INFO("accepted_connection client_ip=%s fd=%d", ip, fd);
 *   LOG_ERROR("parse_failed reason=%s input=%s", err, buf);
 *
 * Log level is set from env var LOG_LEVEL (debug/info/warn/error).
 * Default is info.
 */
#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

enum { LOG_DEBUG_ = 0, LOG_INFO_ = 1, LOG_WARN_ = 2, LOG_ERROR_ = 3 };

static inline int log_level(void)
{
    static int cached = -1;
    if (cached != -1) return cached;
    const char *e = getenv("LOG_LEVEL");
    if (!e)                          cached = LOG_INFO_;
    else if (!strcmp(e, "debug"))    cached = LOG_DEBUG_;
    else if (!strcmp(e, "info"))     cached = LOG_INFO_;
    else if (!strcmp(e, "warn"))     cached = LOG_WARN_;
    else if (!strcmp(e, "error"))    cached = LOG_ERROR_;
    else                             cached = LOG_INFO_;
    return cached;
}

static inline void log_write(int lvl, const char *lvlname,
                             const char *file, int line,
                             const char *fmt, ...)
{
    if (lvl < log_level()) return;

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    fprintf(stderr, "time=%lld.%03ld level=%s src=%s:%d ",
            (long long)ts.tv_sec, ts.tv_nsec / 1000000L,
            lvlname, file, line);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

#define LOG_DEBUG(...) log_write(LOG_DEBUG_, "debug", __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_write(LOG_INFO_,  "info",  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_write(LOG_WARN_,  "warn",  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_ERROR_, "error", __FILE__, __LINE__, __VA_ARGS__)

#endif /* LOG_H */
