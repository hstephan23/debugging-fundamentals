/* 01_heap_overflow.c — write past the end of a heap buffer.
 * Expect: Memcheck "Invalid write of size 4". */
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof(int) * 10);
    for (int i = 0; i <= 10; i++) p[i] = i; /* <-- off by one */
    free(p);
    return 0;
}
