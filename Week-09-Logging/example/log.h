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

#define LOG_(lvl, lvlname, fmt, ...) do {                                 \
    if ((lvl) >= log_level()) {                                           \
        struct timespec _ts;                                              \
        clock_gettime(CLOCK_REALTIME, &_ts);                              \
        fprintf(stderr,                                                   \
                "time=%lld.%03ld level=%s src=%s:%d " fmt "\n",           \
                (long long)_ts.tv_sec, _ts.tv_nsec / 1000000L,            \
                lvlname, __FILE__, __LINE__, ##__VA_ARGS__);              \
    }                                                                      \
} while (0)

#define LOG_DEBUG(fmt, ...) LOG_(LOG_DEBUG_, "debug", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG_(LOG_INFO_,  "info",  fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG_(LOG_WARN_,  "warn",  fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_(LOG_ERROR_, "error", fmt, ##__VA_ARGS__)

#endif /* LOG_H */
