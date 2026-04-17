/* 08_stack_use_after_return.c — return a pointer to a local variable.
 *
 * Valgrind MAY or MAY NOT flag this; Memcheck is weak on stack bugs. This is
 * exactly the kind of case where AddressSanitizer (Week 6) shines —
 * stack-use-after-return is one of its specialties.
 *
 * Keep this exercise as a reminder: Memcheck is not omniscient; different
 * tools see different things. */
#include <stdio.h>

static int *danger(void)
{
    int x = 42;
    return &x;                /* returning address of local */
}

int main(void)
{
    int *p = danger();
    printf("%d\n", *p);       /* may print 42, may print garbage, may crash */
    return 0;
}
