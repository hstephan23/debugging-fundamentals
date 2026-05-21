/*
 * false_sharing.c — correct, but dramatically slow.
 *
 * Two threads each update their own "private" counter, but the two counters
 * sit on the same cache line. The CPUs fight over the cache line on every
 * increment — often 5x–10x slower than the padded version.
 *
 * Compile this one and time it:
 *    time ./false_sharing unpadded
 *    time ./false_sharing padded
 *
 * Then profile with:
 *    perf stat -e cache-misses,cache-references ./false_sharing unpadded
 *    perf c2c record ./false_sharing unpadded
 */
#include <pthread.h>
#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#define N 50000000
#define CACHE_LINE 64

struct unpadded { long a; long b; };
struct padded   { alignas(CACHE_LINE) long a; alignas(CACHE_LINE) long b; };

struct unpadded u;
struct padded   p;

static void *hit_u_a(void *_) { (void)_; for (int i = 0; i < N; i++) u.a++; return NULL; }
static void *hit_u_b(void *_) { (void)_; for (int i = 0; i < N; i++) u.b++; return NULL; }
static void *hit_p_a(void *_) { (void)_; for (int i = 0; i < N; i++) p.a++; return NULL; }
static void *hit_p_b(void *_) { (void)_; for (int i = 0; i < N; i++) p.b++; return NULL; }

int main(int argc, char **argv)
{
    const char *mode = (argc > 1) ? argv[1] : "unpadded";
    pthread_t t1, t2;

    if (strcmp(mode, "padded") == 0) {
        pthread_create(&t1, NULL, hit_p_a, NULL);
        pthread_create(&t2, NULL, hit_p_b, NULL);
    } else {
        pthread_create(&t1, NULL, hit_u_a, NULL);
        pthread_create(&t2, NULL, hit_u_b, NULL);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    puts(mode);
    return 0;
}
