/*
 * race_counter_atomic.c — same counter, fixed with a C11 atomic.
 *
 * Much faster than a mutex for this workload because the primitive is
 * a single hardware instruction (lock xadd on x86). This is what
 * `memory_order_relaxed` is designed for: a counter where you only care
 * about the final value, not ordering relative to other events.
 */
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

#define N 1000000
static atomic_long counter = 0;

static void *worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < N; i++) {
        atomic_fetch_add_explicit(&counter, 1, memory_order_relaxed);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter = %ld (expected %d)\n",
           atomic_load(&counter), 2 * N);
    return 0;
}
