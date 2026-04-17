/*
 * server.c — a tiny fake "server" that does open/read/write in a loop,
 * with structured logs. Great target for strace / ltrace practice.
 *
 *   ./server                     # logs at info
 *   LOG_LEVEL=debug ./server     # much more detail
 *
 *   strace -f -tt -e openat,read,write -p $(pgrep server)
 *   ltrace -p $(pgrep server)
 *
 * Notice how the strace view tells you exactly which files the program
 * touches, and in what order. It's often faster than the debugger.
 */
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"

static volatile sig_atomic_t stop = 0;
static void on_int(int _) { (void)_; stop = 1; }

int main(void)
{
    signal(SIGINT, on_int);
    LOG_INFO("server_start pid=%d", (int)getpid());

    for (long tick = 0; !stop; tick++) {
        LOG_DEBUG("tick value=%ld", tick);

        int fd = open("/etc/hostname", O_RDONLY);
        if (fd < 0) {
            LOG_ERROR("open_failed path=%s errno=%d", "/etc/hostname", errno);
            break;
        }
        char buf[64] = {0};
        ssize_t n = read(fd, buf, sizeof buf - 1);
        close(fd);

        /* strip trailing newline */
        char *nl = strchr(buf, '\n'); if (nl) *nl = 0;

        LOG_INFO("heartbeat tick=%ld host=%s", tick, buf);
        sleep(1);
    }

    LOG_INFO("server_stop");
    return 0;
}
