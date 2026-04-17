/*
 * race_counter.c — the classic racy shared counter.
 *
 * Two threads increment `counter` 1 million times each. Expected final
 * value is 2,000,000; you will usually get less, because `counter++` is
 * (load; add; store) without synchronization.
 *
 * Run it a few times — you'll see different numbers. That non-determinism
 * is the signature of a race.
 *
 * Build under TSan:
 *   make tsan
 *   ./tsan_race
 * TSan will print a precise race report with both accesses' stacks.
 */
#include <pthread.h>
#include <stdio.h>

#define N 1000000
static long counter = 0;

static void *worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < N; i++) counter++;
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter = %ld (expected %d)\n", counter, 2 * N);
    return 0;
}
