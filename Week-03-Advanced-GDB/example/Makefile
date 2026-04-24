# Week 3 — Advanced GDB (watchpoints, scripting, rr)
#
# make              -> builds watchpoint_demo and linked_list
# make rr           -> records an rr trace of watchpoint_demo (needs `rr`)
# make replay       -> `rr replay` the most recent trace
# make clean
#
# Recommended workflow for watchpoint_demo:
#   ./watchpoint_demo           (observe the bad final value of `secret`)
#   gdb ./watchpoint_demo
#     (gdb) break main
#     (gdb) run
#     (gdb) watch secret
#     (gdb) continue            (GDB stops at every write to `secret`)
#
# For reverse debugging:
#   rr record ./watchpoint_demo
#   rr replay
#     (gdb) continue            (land at normal end)
#     (gdb) watch secret
#     (gdb) reverse-continue    (travels backward to the write you care about)

CC     ?= gcc
CFLAGS  = -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

.PHONY: all clean rr replay
all: watchpoint_demo linked_list

watchpoint_demo: watchpoint_demo.c
	$(CC) $(CFLAGS) -o $@ $<

linked_list: linked_list.c
	$(CC) $(CFLAGS) -o $@ $<

rr: watchpoint_demo
	@command -v rr >/dev/null 2>&1 || { \
		echo "rr not found; install rr on Linux to use reverse debugging"; \
		exit 127; \
	}
	rr record ./watchpoint_demo

replay:
	@command -v rr >/dev/null 2>&1 || { \
		echo "rr not found; install rr on Linux to use reverse debugging"; \
		exit 127; \
	}
	rr replay

clean:
	rm -f watchpoint_demo linked_list core core.*
