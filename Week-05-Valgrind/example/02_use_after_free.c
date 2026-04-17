/* 02_use_after_free.c — touch memory after free().
 * Expect: "Invalid read of size 4" + info about the free. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof(int));
    *p = 7;
    free(p);
    printf("%d\n", *p);  /* read after free */
    return 0;
}
