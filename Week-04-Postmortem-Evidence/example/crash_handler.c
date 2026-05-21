/*
 * crash_handler.c — a program that installs a SIGSEGV handler that prints a
 * backtrace before dying. Useful pattern for servers that need to leave a
 * clue on exit, even when a full core dump isn't available.
 *
 * Build:  gcc -g -rdynamic -o crash_handler crash_handler.c
 * Run:    ./crash_handler
 *
 * Note: `-rdynamic` makes symbols available to backtrace_symbols(); without
 * it you'll see only addresses, not names. For deeper traces, use libunwind.
 *
 * Caveats:
 *   - backtrace() is not fully async-signal-safe; for production-grade
 *     reporting, prefer libunwind or a proper crash reporter (breakpad,
 *     Sentry, etc.).
 *   - This intentionally does NOT re-raise the signal, so it exits
 *     cleanly with no core. Change to 'signal(SIGSEGV, SIG_DFL); raise(sig);'
 *     if you also want the core.
 */
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void on_segv(int sig)
{
    void *frames[32];
    int n = backtrace(frames, 32);

    const char msg[] = "\n=== SIGSEGV — backtrace ===\n";
    ssize_t _ = write(STDERR_FILENO, msg, sizeof(msg) - 1); (void)_;

    backtrace_symbols_fd(frames, n, STDERR_FILENO);
    _exit(128 + sig);
}

static void boom(void)
{
    int *p = NULL;
    *p = 42;    /* null deref */
}

int main(void)
{
    struct sigaction sa = {0};
    sa.sa_handler = on_segv;
    sigaction(SIGSEGV, &sa, NULL);

    puts("about to crash...");
    boom();
    return 0;
}
