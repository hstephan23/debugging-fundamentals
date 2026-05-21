/*
 * cond_spurious.c — demonstrates why pthread_cond_wait MUST be in a while loop.
 *
 * A third thread fires extra pthread_cond_signal calls that don't correspond
 * to real new work. If the consumer uses `if` instead of `while`, it can wake
 * up and continue even though the queue is still empty. A real queue pop here
 * would underflow or read stale data.
 *
 * Flip USE_IF_BUG between 0 and 1 to see the difference.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define USE_IF_BUG 1   /* <-- flip to 0 to fix */

#define CAP 8
static int  q[CAP];
static int  n = 0;
static pthread_mutex_t m  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cv = PTHREAD_COND_INITIALIZER;
static int done = 0;
static int empty_wakeups = 0;

static void *producer(void *_)
{
    (void)_;
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&m);
        while (n == CAP) { pthread_mutex_unlock(&m); usleep(1000); pthread_mutex_lock(&m); }
        q[n++] = i;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&m);
        usleep(1000);
    }
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);
    return NULL;
}

static void *consumer(void *_)
{
    (void)_;
    for (;;) {
        pthread_mutex_lock(&m);
#if USE_IF_BUG
        if (n == 0)                  /* BUG: not re-checked */
            pthread_cond_wait(&cv, &m);
        if (n == 0 && !done) {
            empty_wakeups++;
            if (empty_wakeups <= 5) {
                puts("BUG: woke up with no item; if-version did not re-check");
            }
            pthread_mutex_unlock(&m);
            continue;
        }
#else
        while (n == 0 && !done)      /* correct */
            pthread_cond_wait(&cv, &m);
#endif
        if (n == 0 && done) {
            pthread_mutex_unlock(&m);
            break;
        }
        if (n > 0) {
            int v = q[--n];
            printf("got %d\n", v);
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

/* Adversary: blasts spurious signals. Simulates what glibc may do anyway. */
static void *spurious(void *_)
{
    (void)_;
    for (int i = 0; i < 50; i++) {
        pthread_mutex_lock(&m);
        if (done) {
            pthread_mutex_unlock(&m);
            break;
        }
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&m);
        usleep(500);
    }
    return NULL;
}

int main(void)
{
    pthread_t p, c, s;
    pthread_create(&c, NULL, consumer, NULL);
    pthread_create(&s, NULL, spurious, NULL);
    usleep(2000); /* let the consumer block before fake signals arrive */
    pthread_create(&p, NULL, producer, NULL);
    pthread_join(p, NULL);
    pthread_join(s, NULL);
    pthread_join(c, NULL);
    if (empty_wakeups > 0) {
        printf("empty_wakeups=%d\n", empty_wakeups);
    }
    return 0;
}
