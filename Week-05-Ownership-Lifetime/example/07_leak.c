/* 07_leak.c — a pointer goes out of scope without freeing.
 * Expect: "X bytes in Y blocks are definitely lost". */
#include <stdlib.h>

static void loser(void)
{
    char *p = malloc(64);
    (void)p;           /* p dies with the function; the malloc is lost */
}

int main(void)
{
    for (int i = 0; i < 3; i++) loser();
    return 0;
}
