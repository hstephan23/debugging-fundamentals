/*
 * deadlock_fixed.c — same workload, fixed by enforcing a consistent
 * lock order: ALWAYS acquire A before B.
 *
 * This is the cheapest deadlock-prevention strategy and the most common
 * in real codebases. Write it down for your project — even in a README —
 * and enforce it in code review.
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
    pthread_mutex_lock(&B);
    puts("t1: both");
    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    return NULL;
}

static void *t2_fn(void *_)
{
    (void)_;
    pthread_mutex_lock(&A);      /* was B — swapped */
    pthread_mutex_lock(&B);
    puts("t2: both");
    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, t1_fn, NULL);
    pthread_create(&t2, NULL, t2_fn, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    puts("done");
    return 0;
}
