/*
 * asan_demo.c — a menu of bugs ASan catches crisply.
 *
 * Build:  make asan
 * Run:    ./asan_demo 1    # heap overflow
 *         ./asan_demo 2    # use after free
 *         ./asan_demo 3    # stack buffer overflow
 *         ./asan_demo 4    # stack use after return
 *         ./asan_demo 5    # use after scope
 *         ./asan_demo 6    # leak (reported at exit)
 *
 * Notice how the ASan report includes a shadow-memory diagram under each
 * error — it tells you exactly which byte was poisoned and why.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *leak_later(void)
{
    int x = 7;
    return &x;              /* dangling; used by caller in case 4 */
}

static int *use_after_scope(void)
{
    int *p;
    {
        int local = 99;
        p = &local;         /* `local` dies at the end of this block */
    }
    return p;
}

int main(int argc, char **argv)
{
    int which = (argc > 1) ? atoi(argv[1]) : 1;

    switch (which) {
    case 1: {               /* heap overflow */
        int *a = malloc(sizeof(int) * 4);
        a[4] = 0;           /* one past the end */
        free(a);
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
        strcpy(buf, "this is too long for 8 bytes");
        puts(buf);
        break;
    }
    case 4: {               /* stack use after return */
        int *p = leak_later();
        printf("%d\n", *p);
        break;
    }
    case 5: {               /* stack use after scope */
        int *p = use_after_scope();
        printf("%d\n", *p);
        break;
    }
    case 6: {               /* leak — reported on exit by LSan */
        (void)malloc(128);
        break;
    }
    default:
        fprintf(stderr, "usage: %s 1..6\n", argv[0]);
        return 2;
    }
    return 0;
}
