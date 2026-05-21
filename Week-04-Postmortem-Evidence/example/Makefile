# Week 4 — Core Dumps & Postmortem
#
# make              -> builds `crash` and `crash_handler`
# make split        -> demonstrates split debuginfo (produces .debug file)
# make clean
#
# After building, enable core dumps in your shell:
#   ulimit -c unlimited
#   ./crash "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#
# Then inspect:
#   gdb ./crash ./core          (or  coredumpctl gdb crash)
#     (gdb) bt
#     (gdb) frame 2
#     (gdb) info args
#     (gdb) info locals

CC     ?= gcc
CFLAGS  = -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

.PHONY: all clean split

all: crash crash_handler

crash: crash.c
	$(CC) $(CFLAGS) -o $@ $<

crash_handler: crash_handler.c
	$(CC) $(CFLAGS) -rdynamic -o $@ $< -ldl

# Demonstrate the production pattern: strip binary, archive .debug file
split: crash
	objcopy --only-keep-debug crash crash.debug
	strip --strip-debug crash
	objcopy --add-gnu-debuglink=crash.debug crash
	@echo
	@echo "Now 'file crash' shows it stripped, but gdb still finds symbols"
	@echo "via crash.debug in the same directory."

clean:
	rm -f crash crash.debug crash_handler core core.*
