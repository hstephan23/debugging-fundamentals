/* 03_double_free.c — free the same block twice.
 * Expect: "Invalid free() / delete / delete[] / realloc()" with both
 * free stack traces. */
#include <stdlib.h>

int main(void)
{
    void *p = malloc(32);
    free(p);
    free(p);   /* second free: bug */
    return 0;
}
