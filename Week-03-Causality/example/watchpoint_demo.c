/*
 * watchpoint_demo.c
 *
 * `secret` should end at 42. Somewhere along the way, ONE of the called
 * functions overwrites it with garbage. Instead of adding print statements
 * everywhere, use a GDB watchpoint:
 *
 *   (gdb) break main
 *   (gdb) run
 *   (gdb) watch secret
 *   (gdb) continue
 *
 * GDB will stop the program at the exact instruction that writes `secret`.
 * Walk the stack, and you have the culprit.
 *
 * For reverse debugging under `rr`:
 *   rr record ./watchpoint_demo
 *   rr replay
 *     (rr) continue
 *     (rr) watch secret
 *     (rr) reverse-continue
 */
#include <stdio.h>

static int secret = 42;

static void innocent_a(void) { /* pretends to do nothing wrong */ }
static void innocent_b(void) { secret = 0xDEAD; /* the culprit */ }
static void innocent_c(void) { /* also innocent */ }

int main(void)
{
    printf("before: secret=%d\n", secret);

    innocent_a();
    innocent_b();   /* <-- this is the one; but pretend you don't know that */
    innocent_c();

    printf("after : secret=%d (expected 42)\n", secret);
    return 0;
}
