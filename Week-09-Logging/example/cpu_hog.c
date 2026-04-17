/*
 * cpu_hog.c — three functions that each spend noticeable CPU, on purpose.
 *
 *   perf record -g ./cpu_hog
 *   perf report
 *
 * You should see hot_a, hot_b, and hot_c near the top of the profile.
 * Generate a flamegraph with Brendan Gregg's scripts for bonus points.
 */
#include <math.h>
#include <stdio.h>

static double hot_a(long n)
{
    double s = 0;
    for (long i = 0; i < n; i++) s += sin((double)i);
    return s;
}

static double hot_b(long n)
{
    double s = 0;
    for (long i = 0; i < n; i++) s += cos((double)i) * cos((double)i);
    return s;
}

static double hot_c(long n)
{
    double s = 0;
    for (long i = 1; i < n; i++) s += log((double)i);
    return s;
}

int main(void)
{
    double r = 0;
    for (int i = 0; i < 3; i++) {
        r += hot_a(10000000);
        r += hot_b(10000000);
        r += hot_c(10000000);
    }
    printf("r=%g\n", r);
    return 0;
}
