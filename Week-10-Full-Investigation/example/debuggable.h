/*
 * debuggable.h — a tiny header of "debuggable by default" helpers.
 *
 * Drop this into your capstone (or any C project) and use:
 *
 *   EXPECT(ptr != NULL);                    // always on; abort on failure
 *   DEBUG_ONLY(expensive_invariant_check()); // only in debug builds
 *
 *   int fd = open("foo", O_RDONLY);
 *   CHECK_SYSCALL(fd >= 0, "open foo");      // logs errno, aborts or returns
 *
 *   char *buf;
 *   SCOPE_FREE(buf) = malloc(64);            // auto-free at end of scope (GCC/Clang)
 *
 * Design notes:
 *   - EXPECT is assert() that survives NDEBUG. Use it for preconditions on
 *     data you got from outside the function. Keep real assert() for
 *     invariants that are truly internal.
 *   - Structured error output is cheaper to read than prose under stress.
 *   - SCOPE_FREE uses __attribute__((cleanup)), supported by GCC and Clang.
 */
#ifndef DEBUGGABLE_H
#define DEBUGGABLE_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Assertion that stays enabled even with -DNDEBUG. */
#define EXPECT(cond)                                                           \
    do {                                                                       \
        if (!(cond)) {                                                         \
            fprintf(stderr,                                                    \
                    "EXPECT failed: %s\n  at %s:%d in %s\n",                   \
                    #cond, __FILE__, __LINE__, __func__);                      \
            abort();                                                           \
        }                                                                      \
    } while (0)

/* Runs only in debug builds. Put expensive invariant checks here. */
#ifdef NDEBUG
  #define DEBUG_ONLY(stmt) do { } while (0)
#else
  #define DEBUG_ONLY(stmt) do { stmt; } while (0)
#endif

/* Syscall wrapper: aborts with a structured message on failure. */
#define CHECK_SYSCALL(ok, what)                                                \
    do {                                                                       \
        if (!(ok)) {                                                           \
            fprintf(stderr,                                                    \
                    "syscall_failed what=\"%s\" errno=%d msg=\"%s\"\n"         \
                    "  at %s:%d\n",                                            \
                    (what), errno, strerror(errno), __FILE__, __LINE__);       \
            abort();                                                           \
        }                                                                      \
    } while (0)

/* RAII-ish free on scope exit (GCC / Clang extension). */
static inline void _auto_free(void *pp) {
    void **p = (void **)pp;
    if (p && *p) { free(*p); *p = NULL; }
}
#define SCOPE_FREE(var) __attribute__((cleanup(_auto_free))) var

#endif /* DEBUGGABLE_H */
