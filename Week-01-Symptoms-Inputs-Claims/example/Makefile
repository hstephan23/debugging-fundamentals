# Week 1 — Foundations & Methodology
#
# Two build modes: debug and release.
#   make debug       -> ./sum_debug   (unoptimized, full debug info, loud warnings)
#   make release     -> ./sum_release (optimized; the bug may look different!)
#   make run-debug   -> run the debug binary; assertion failure is expected
#   make run-release -> run the release binary; assertion is compiled out
#   make clean       -> remove build artifacts
#
# The point of having both is to internalize that *the same source* can behave
# differently depending on how you compile it. Debug builds are for
# understanding; release builds are for shipping.

CC       ?= gcc

WARN     = -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2
COMMON   = -std=c11 $(WARN) -fno-omit-frame-pointer

DEBUG    = -O0 -g3 -fno-common -D_FORTIFY_SOURCE=0
RELEASE  = -O2 -g  -DNDEBUG

SRC      = main.c utils.c

.PHONY: all debug release clean run-debug run-release

all: debug

debug: sum_debug

release: sum_release

sum_debug: $(SRC) utils.h
	$(CC) $(COMMON) $(DEBUG) -o $@ $(SRC)

sum_release: $(SRC) utils.h
	$(CC) $(COMMON) $(RELEASE) -o $@ $(SRC)

run-debug: sum_debug
	@./sum_debug; status=$$?; \
	if [ $$status -ne 0 ]; then \
		printf "\nexpected: debug build tripped the assertion because the bug is still present (exit=%d)\n" "$$status"; \
	fi

run-release: sum_release
	./sum_release

clean:
	rm -f sum_debug sum_release *.o core core.*
