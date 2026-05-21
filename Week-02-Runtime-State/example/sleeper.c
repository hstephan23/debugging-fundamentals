/*
 * sleeper.c — a long-running process for "attach to a running program"
 * practice.
 *
 * Run it in one terminal:   ./sleeper
 * Attach from another:       gdb -p $(pgrep sleeper)
 *
 * Inside GDB:
 *   bt                      -> see where it's blocked (probably nanosleep)
 *   info locals
 *   p counter
 *   set counter = 999       -> (yes, you can modify live state)
 *   continue
 *   detach                  -> leave the process running; don't `quit`!
 *
 * If attach fails with "ptrace: Operation not permitted" on Linux:
 *   sudo sysctl -w kernel.yama.ptrace_scope=0   # temporary, for this session
 */
#include <stdio.h>
#include <unistd.h>

static volatile long counter = 0;

int main(void)
{
    printf("sleeper pid=%d — attach with `gdb -p %d`\n",
           (int)getpid(), (int)getpid());
    fflush(stdout);

    for (;;) {
        counter++;
        sleep(1);
    }
    return 0;
}
