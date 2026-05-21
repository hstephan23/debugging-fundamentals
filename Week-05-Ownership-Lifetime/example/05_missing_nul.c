/* 05_missing_nul.c — build a string without a terminating NUL.
 * Expect: Memcheck complains when strlen/printf reads past the buffer. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = malloc(3);  /* no room for NUL */
    s[0] = 'h';
    s[1] = 'i';
    s[2] = '!';           /* oops — should have been '\0' */
    printf("len=%zu s=%s\n", strlen(s), s);
    free(s);
    return 0;
}
