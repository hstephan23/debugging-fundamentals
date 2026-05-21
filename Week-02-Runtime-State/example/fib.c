/*
 * fib.c — recursive Fibonacci with a tiny memoization cache.
 *
 * Small enough to step through comfortably, branchy enough that the call
 * stack becomes interesting. Perfect terrain for practising:
 *   b fib
 *   b fib.c:LINE if n == 5
 *   bt, frame N, info args, info locals
 *   display memo[n]
 *   commands ... silent ... printf ... continue ... end
 *
 * Usage: ./fib <n>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 64
static long memo[MAX];
static int  have[MAX];

static long fib(int n)
{
    if (n < 2)         return n;
    if (have[n])       return memo[n];

    long r = fib(n - 1) + fib(n - 2);
    memo[n] = r;
    have[n] = 1;
    return r;
}

int main(int argc, char **argv)
{
    memset(memo, 0, sizeof(memo));
    memset(have, 0, sizeof(have));

    int n = (argc > 1) ? atoi(argv[1]) : 10;
    if (n < 0 || n >= MAX) {
        fprintf(stderr, "n must be in [0, %d)\n", MAX);
        return 1;
    }

    long r = fib(n);
    printf("fib(%d) = %ld\n", n, r);
    return 0;
}
