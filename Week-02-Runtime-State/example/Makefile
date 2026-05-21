# Week 2 — GDB Fundamentals
#
# Builds:
#   make         -> all programs
#   make fib     -> recursive memoized Fibonacci (practice stepping, frames)
#   make sleeper -> long-running process for 'gdb -p' attach practice
#   make clean
#
# Suggested GDB session (after `make`):
#   gdb ./fib
#   (gdb) break fib
#   (gdb) run 10
#   (gdb) bt
#   (gdb) info args
#   (gdb) finish
#   ...

CC     ?= gcc
CFLAGS  = -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

.PHONY: all clean
all: fib sleeper

fib: fib.c
	$(CC) $(CFLAGS) -o $@ $<

sleeper: sleeper.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f fib sleeper core core.*
