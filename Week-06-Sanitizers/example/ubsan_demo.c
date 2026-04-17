/*
 * ubsan_demo.c — flavors of undefined behavior UBSan will catch.
 *
 * Build:  make ubsan
 * Run:    ./ubsan_demo 1   # signed integer overflow
 *         ./ubsan_demo 2   # shift by too many bits
 *         ./ubsan_demo 3   # misaligned pointer
 *         ./ubsan_demo 4   # out-of-range enum / array
 *         ./ubsan_demo 5   # null pointer dereference
 *
 * UBSan prints a pinpoint report with file:line and what went wrong.
 * Without UBSan, these are all UB — the compiler is free to do anything,
 * including silently generating "optimized" code that skips the check.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(int argc, char **argv)
{
    int which = (argc > 1) ? atoi(argv[1]) : 1;

    switch (which) {
    case 1: {                               /* signed overflow */
        int x = INT_MAX;
        x += 1;
        printf("x = %d\n", x);
        break;
    }
    case 2: {                               /* bad shift */
        int x = 1;
        int n = 40;                         /* int is 32 bits; shifting by >=32 is UB */
        printf("1 << 40 = %d\n", x << n);
        break;
    }
    case 3: {                               /* misaligned pointer load */
        char buf[8] = {0};
        int *misaligned = (int *)(buf + 1); /* not 4-byte aligned */
        printf("%d\n", *misaligned);
        break;
    }
    case 4: {                               /* out-of-range array index */
        int a[4] = {0,1,2,3};
        int i = 5;                          /* UBSan with -fsanitize=bounds flags this */
        printf("a[%d]=%d\n", i, a[i]);
        break;
    }
    case 5: {                               /* null deref */
        int *p = NULL;
        *p = 42;
        break;
    }
    default:
        fprintf(stderr, "usage: %s 1..5\n", argv[0]);
        return 2;
    }
    return 0;
}
