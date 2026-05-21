# Week 6 — Sanitizers (ASan, UBSan, LSan)
#
# Rebuild the same sources under different sanitizers and observe what each
# one catches.
#
#   make asan        -> binary under AddressSanitizer; LeakSanitizer where supported
#   make ubsan       -> binaries under UBSan only (catch UB at runtime)
#   make clean
#
# Then run:
#   ./asan_demo
#   ./ubsan_demo

CC     ?= gcc
CFLAGS_COMMON = -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

ASAN_FLAGS  = -fsanitize=address -fno-sanitize-recover=all
UBSAN_FLAGS = -fsanitize=undefined -fno-sanitize-recover=undefined

.PHONY: all asan ubsan clean

all: asan ubsan

asan: asan_demo

asan_demo: asan_demo.c
	$(CC) $(CFLAGS_COMMON) $(ASAN_FLAGS) -o $@ $<

ubsan: ubsan_demo

ubsan_demo: ubsan_demo.c
	$(CC) $(CFLAGS_COMMON) $(UBSAN_FLAGS) -o $@ $<

clean:
	rm -f asan_demo ubsan_demo core core.*
