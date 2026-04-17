# Week 9 — Logging, Tracing & Observability
#
# make              -> build server + cpu_hog
# make clean
#
# Practice ideas:
#   ./server &             # runs, logs structured lines to stderr
#   strace -f -tt -e openat,read,write -p $(pgrep server)
#   perf record -g ./cpu_hog
#   perf report

CC     ?= gcc
CFLAGS  = -O2 -g -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

TARGETS = server cpu_hog

.PHONY: all clean
all: $(TARGETS)

server: server.c log.h
	$(CC) $(CFLAGS) -o $@ $<

cpu_hog: cpu_hog.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) core core.*
