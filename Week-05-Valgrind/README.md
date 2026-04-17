# Week 5 — Memory Bugs with Valgrind

## Goal

Develop real fluency with Valgrind's Memcheck — the classic, still-indispensable tool for finding memory errors in C. By the end of the week you should be able to read a Memcheck report like English and know exactly what it's telling you.

## Concepts to understand

- **Valgrind is a dynamic binary instrumentation framework.** It re-translates every instruction and layers checkers on top. It's slow (10×–50× typical) but catches things static tools cannot.
- **Memcheck tracks two things per byte: is it allocated, and is it initialized?** Nearly every Memcheck error reduces to one of those questions being answered "no."
- **The major error categories:**
  - *Invalid read/write* — reading or writing unallocated memory (heap overflow, use-after-free, wild pointer).
  - *Use of uninitialized value* — using memory whose contents were never written.
  - *Memory leak* — allocations that were never freed. Memcheck distinguishes *definitely lost*, *indirectly lost*, *possibly lost*, and *still reachable*.
  - *Mismatched free* — `free()` on a `new[]`, or `malloc` / `delete`, or double-free.
- **Suppression files** let you silence warnings you've investigated and deemed unfixable (e.g., in third-party libraries). Use them sparingly and document why.
- **Memcheck misses stack overflows and doesn't cover all of the standard library.** It's superb for heap bugs; weak on stack corruption. That's where ASan (next week) complements it.

## Reading / watching

- Valgrind manual, Memcheck section — read it cover to cover at least once. It's short and everything matters.
- "Valgrind Quick Start" from the official site.
- A couple of real-world Valgrind war stories (Julia Evans has several short posts; so does LWN.net).

## Core practice

### 1. Make friends with the output format

Compile with `-g -O0`. Run a simple bug:

```c
// leak.c
#include <stdlib.h>
int main(void) {
    int *p = malloc(sizeof(int) * 10);
    p[10] = 42;           // heap overflow
    // no free             // leak
    return 0;
}
```

Run:

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./leak
```

Read every line of the output. Map each reported error to the concept:

- Which line is the heap overflow?
- Which allocation does the leak report point back to?
- What does "1 block are definitely lost" actually mean?

### 2. Common patterns to reproduce deliberately

Build a bug buffet — one tiny program per bug — and diagnose each:

1. Buffer overflow on the heap
2. Use-after-free (free, then dereference)
3. Double-free
4. Use of uninitialized memory (`malloc` without initializing, then read)
5. Forgetting the null terminator on a string
6. Off-by-one writing the sentinel
7. Memory leak with a pointer lost mid-function
8. Use of a stack variable after the function returned (Memcheck will struggle with this — that's the point)

For each, read the Memcheck report and *predict* what it will say before re-running. This is how you learn to diagnose from the report alone.

### 3. `--track-origins=yes`

This flag makes Memcheck track, for uninitialized-value errors, where the uninitialized memory originated. It's slower, so it's off by default — but during investigation it's the difference between "something uninitialized somewhere" and "here is the exact malloc that was never written to."

Run a reproducer with and without the flag. Notice the difference in the report.

### 4. Suppressions

Write a small program that intentionally uses a library with a known "leak" that you want to ignore (or fake it with a helper function). Generate a suppression:

```
valgrind --gen-suppressions=yes ./myprog
```

Then write a `.supp` file with the suppressions you deliberately want, and invoke:

```
valgrind --suppressions=./my.supp ./myprog
```

Get a feel for suppression syntax. Rule of thumb: if you're writing a suppression, leave a comment explaining *why* — otherwise the next person just inherits a silence.

### 5. Integrate Valgrind into your test run

Modify your `Makefile` so `make check-mem` runs your test suite under Memcheck with exit code 1 on errors:

```make
check-mem:
    valgrind --leak-check=full --error-exitcode=1 ./run_tests
```

Once Memcheck is wired into your test target, it catches bugs on every run — and you stop forgetting to use it.

## Stretch

- Try other Valgrind tools: `cachegrind` for cache behavior, `callgrind` for call graphs, `massif` for heap profiling. You won't use them every day but knowing they exist is valuable.
- Read one of the Memcheck papers from the Valgrind team (Nethercote &amp; Seward). The design choices are elegant.
- Compare output between Valgrind and an ASan build of the same bug (preview of next week). Notice what each tool catches that the other misses.

## Checkpoint

You can move to Week 6 when you can:

- Explain what Memcheck tracks per byte and how that maps to the main error categories.
- Read a `==PID==` report and translate it to a specific line of code and a specific bug class.
- Tell "definitely lost" from "still reachable" in a leak report and explain when each matters.
- Use `--track-origins=yes` appropriately and know its cost.
- Run your test suite under Memcheck as a CI-style gate.
