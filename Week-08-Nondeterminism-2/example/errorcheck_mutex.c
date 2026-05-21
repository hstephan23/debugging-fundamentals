/*
 * errorcheck_mutex.c — the same thread locks the same mutex twice.
 *
 * With PTHREAD_MUTEX_NORMAL (the default), this is undefined behavior —
 * often a self-deadlock that just hangs.
 *
 * With PTHREAD_MUTEX_ERRORCHECK, pthread_mutex_lock returns EDEADLK
 * instead, and you can actually handle the bug. Useful during development,
 * especially in codebases with deep call chains where it's easy to lose
 * track of what's locked.
 *
 * Toggle USE_ERRORCHECK and compare the behavior.
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

#define USE_ERRORCHECK 1

static pthread_mutex_t m;

int main(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#if USE_ERRORCHECK
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
#else
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
#endif
    pthread_mutex_init(&m, &attr);

    int r = pthread_mutex_lock(&m);
    printf("first  lock -> %d\n", r);

    r = pthread_mutex_lock(&m);
    printf("second lock -> %d (%s)\n", r,
           r == EDEADLK ? "EDEADLK — caught!" : "undefined (probably hung)");

    pthread_mutex_unlock(&m);
    pthread_mutex_destroy(&m);
    pthread_mutexattr_destroy(&attr);
    return 0;
}
