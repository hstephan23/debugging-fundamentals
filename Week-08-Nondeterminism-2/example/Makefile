# Week 8 — Concurrency II: Deadlocks & Live Thread Debugging
#
#   make                -> plain builds
#   make helgrind       -> runs deadlock under helgrind
#   make clean
#
# For the classic two-lock deadlock:
#   ./deadlock           (will hang — Ctrl-C after a few seconds)
#   gdb -p $(pgrep deadlock)
#     (gdb) thread apply all bt
#
# Or under helgrind:
#   valgrind --tool=helgrind ./deadlock
#
# For the fixed version:
#   ./deadlock_fixed     (terminates normally)

CC     ?= gcc
CFLAGS  = -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11
LDLIBS  = -lpthread

TARGETS = deadlock deadlock_fixed errorcheck_mutex cond_spurious

.PHONY: all helgrind clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

helgrind: deadlock
	@command -v valgrind >/dev/null 2>&1 || { \
		echo "valgrind not found; install Valgrind to use Helgrind"; \
		exit 127; \
	}
	valgrind --tool=helgrind ./deadlock

clean:
	rm -f $(TARGETS) core core.*
