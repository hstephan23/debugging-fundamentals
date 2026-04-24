# Week 5 — Memory Bugs with Valgrind
#
# A "bug buffet" — one tiny program per bug class. Build everything, then
# run each under Memcheck.
#
#   make
#   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./01_heap_overflow
#   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./02_use_after_free
#   ...
#
# Or:
#   make check-all    -> runs valgrind on every target
#
# Predict what Memcheck will say BEFORE running. That's the exercise.

CC     ?= gcc
CFLAGS  = -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer -std=c11

TARGETS = 01_heap_overflow 02_use_after_free 03_double_free \
          04_uninitialized 05_missing_nul 06_off_by_one_write \
          07_leak 08_stack_use_after_return

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes \
                 --error-exitcode=1

.PHONY: all clean check-all
all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

check-all: all
	@command -v valgrind >/dev/null 2>&1 || { \
		echo "valgrind not found; install Valgrind or run the Week 6 sanitizer examples instead"; \
		exit 127; \
	}
	@for t in $(TARGETS); do \
		echo "\n===== $$t ====="; \
		valgrind $(VALGRIND_FLAGS) ./$$t || true; \
	done

clean:
	rm -f $(TARGETS) core core.*
