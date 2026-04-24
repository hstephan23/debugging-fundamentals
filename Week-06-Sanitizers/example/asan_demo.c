/*
 * asan_demo.c — a menu of bugs ASan catches crisply.
 *
 * Build:  make asan
 * Run:    ./asan_demo 1    # heap overflow
 *         ./asan_demo 2    # use after free
 *         ./asan_demo 3    # stack buffer overflow
 *         ./asan_demo 4    # double free
 *         ./asan_demo 5    # global buffer overflow
 *         ./asan_demo 6    # leak (reported at exit where LSan is supported)
 *
 * Notice how the ASan report includes a shadow-memory diagram under each
 * error — it tells you exactly which byte was poisoned and why.
 */
#include <stdio.h>
#include <stdlib.h>

static int global[4];

int main(int argc, char **argv)
{
    int which = (argc > 1) ? atoi(argv[1]) : 1;

    switch (which) {
    case 1: {               /* heap overflow */
        volatile int *a = malloc(sizeof(int) * 4);
        a[4] = 0;           /* one past the end */
        free((void *)a);
        break;
    }
    case 2: {               /* use after free */
        int *a = malloc(sizeof(int));
        *a = 1;
        free(a);
        printf("%d\n", *a);
        break;
    }
    case 3: {               /* stack buffer overflow */
        char buf[8];
        volatile char *p = buf;
        for (int i = 0; i < 16; i++) p[i] = 'A';
        buf[7] = '\0';
        puts(buf);
        break;
    }
    case 4: {               /* double free */
        volatile int *p = malloc(sizeof *p);
        *p = 1;
        free((void *)p);
        free((void *)p);
        break;
    }
    case 5: {               /* global buffer overflow */
        volatile int *p = global;
        p[4] = 99;
        break;
    }
    case 6: {               /* leak — reported on exit where LSan is supported */
        char *p = malloc(128);
        p[0] = 'x';
        printf("leaked allocation starts with %c\n", p[0]);
        break;
    }
    default:
        fprintf(stderr, "usage: %s 1..6\n", argv[0]);
        return 2;
    }
    return 0;
}
