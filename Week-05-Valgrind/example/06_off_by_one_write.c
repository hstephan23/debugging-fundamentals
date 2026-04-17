/* 06_off_by_one_write.c — classic strcpy into a buffer with no room for NUL.
 * Expect: "Invalid write of size 1". */
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char *msg = "hello";        /* 5 chars + NUL = 6 bytes */
    char *buf = malloc(strlen(msg));  /* one byte short */
    strcpy(buf, msg);                 /* writes the NUL past the end */
    free(buf);
    return 0;
}
