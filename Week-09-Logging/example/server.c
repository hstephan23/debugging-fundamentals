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

        const char *paths[] = { "/etc/hostname", "/etc/hosts" };
        const char *path = NULL;
        int fd = -1;

        for (size_t i = 0; i < sizeof paths / sizeof paths[0]; i++) {
            fd = open(paths[i], O_RDONLY);
            if (fd >= 0) {
                path = paths[i];
                break;
            }
        }
        if (fd < 0) {
            LOG_ERROR("open_failed paths=%s,%s errno=%d",
                      paths[0], paths[1], errno);
            break;
        }
        char buf[64] = {0};
        ssize_t n = read(fd, buf, sizeof buf - 1);
        if (n < 0) {
            LOG_ERROR("read_failed path=%s errno=%d", path, errno);
            close(fd);
            break;
        }
        buf[n] = '\0';
        close(fd);

        /* strip trailing newline */
        char *nl = strchr(buf, '\n'); if (nl) *nl = 0;

        LOG_INFO("heartbeat tick=%ld path=%s bytes=%zd sample=%s",
                 tick, path, n, buf);
        sleep(1);
    }

    LOG_INFO("server_stop");
    return 0;
}
