# Week 7 — Concurrency I: Data Races & ThreadSanitizer
#
#   make             -> plain builds of every program
#   make tsan        -> same programs under ThreadSanitizer
#   make clean
#
# Then:
#   ./race_counter            (run a few times — note the varying results)
#   ./race_counter_mutex      (always 2_000_000)
#   ./race_counter_atomic     (always 2_000_000)
#   ./tsan_race               (TSan reports the race with full stacks)

CC     ?= gcc
CFLAGS  = -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11
LDLIBS  = -lpthread

TSAN    = -fsanitize=thread

TARGETS = race_counter race_counter_mutex race_counter_atomic false_sharing

.PHONY: all tsan clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

tsan: tsan_race

tsan_race: race_counter.c
	$(CC) $(CFLAGS) $(TSAN) -o $@ $< $(LDLIBS)

clean:
	rm -f $(TARGETS) tsan_race core core.*
