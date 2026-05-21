/* 04_uninitialized.c — branch on uninitialised data.
 * Expect: "Conditional jump or move depends on uninitialised value(s)"
 * and with --track-origins=yes a pointer back to the malloc site. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof(int));   /* deliberately not calloc */
    if (*p > 0) {                   /* uninitialised read */
        puts("positive");
    } else {
        puts("not positive");
    }
    free(p);
    return 0;
}
