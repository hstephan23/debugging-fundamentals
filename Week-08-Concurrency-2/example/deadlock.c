/*
 * deadlock.c — classic two-lock AB-BA deadlock.
 *
 * Thread 1: lock A, sleep a bit, try to lock B
 * Thread 2: lock B, sleep a bit, try to lock A
 *
 * Both block forever, each holding what the other wants.
 *
 * How to debug:
 *   Run:    ./deadlock
 *   In another terminal:
 *       gdb -p $(pgrep deadlock)
 *       (gdb) info threads
 *       (gdb) thread apply all bt
 *
 *   Each thread is blocked in a futex-wait; the stack frame above tells
 *   you which mutex. Then look at which mutex each thread already HOLDS
 *   (you may need to peek at the thread's locals or the mutex owner).
 *
 * Alternative:
 *   valgrind --tool=helgrind ./deadlock
 *   (reports lock-order violations directly)
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

static void *t1_fn(void *_)
{
    (void)_;
    pthread_mutex_lock(&A);
    puts("t1: got A, sleeping before B...");
    usleep(100 * 1000);
    pthread_mutex_lock(&B);      /* wants B — will block */
    puts("t1: got both");
    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    return NULL;
}

static void *t2_fn(void *_)
{
    (void)_;
    pthread_mutex_lock(&B);
    puts("t2: got B, sleeping before A...");
    usleep(100 * 1000);
    pthread_mutex_lock(&A);      /* wants A — will block */
    puts("t2: got both");
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&B);
    return NULL;
}

int main(void)
{
    printf("deadlock pid=%d (attach with `gdb -p %d`)\n",
           (int)getpid(), (int)getpid());
    fflush(stdout);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, t1_fn, NULL);
    pthread_create(&t2, NULL, t2_fn, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    puts("done");
    return 0;
}
