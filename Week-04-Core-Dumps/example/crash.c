/*
 * crash.c — a deliberately crashable program, realistic in structure.
 *
 * The crash happens inside greet() which calls strcpy() into a fixed
 * 16-byte buffer. A caller passing a long argument clobbers the stack
 * and segfaults on return. Classic.
 *
 * Usage: ./crash "some long string"
 *
 * Exercise:
 *   1. Run with a short argument — fine.
 *   2. Run with a long argument — crashes.
 *   3. Load the core in gdb, walk the stack, and explain to yourself
 *      how the argument got from main() -> greet() and what happened
 *      in between. `info args` at each frame is your friend.
 */
#include <stdio.h>
#include <string.h>

static void greet(const char *name)
{
    char buf[16];           /* deliberately tiny */
    strcpy(buf, "Hello, "); /* unsafe by design */
    strcat(buf, name);      /* overflows for names > ~8 bytes */
    puts(buf);
}

static void run(const char *name)
{
    greet(name);
    /* Return address on stack is probably smashed by now. */
}

int main(int argc, char **argv)
{
    const char *name = (argc > 1) ? argv[1] : "world";
    run(name);
    return 0;
}
