/*
 * race_counter_mutex.c — same as race_counter.c, fixed with a mutex.
 * Slow but obviously correct. TSan reports no race.
 */
#include <pthread.h>
#include <stdio.h>

#define N 1000000
static long counter = 0;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&m);
        counter++;
        pthread_mutex_unlock(&m);
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

    printf("counter = %ld (expected %d)\n", counter, 2 * N);
    return 0;
}
