# Week 6 — Sanitizers (ASan, UBSan, LSan, MSan)

## Goal

Learn the modern sanitizer family — compiler-based runtime checkers that catch memory and undefined-behavior bugs with dramatically less overhead than Valgrind. By the end of the week, sanitizer builds should be a standard part of your development loop.

## 30-minute pass

- **0–5 min:** Read what ASan and UBSan catch, and how that differs from Valgrind.
- **5–14 min:** `cd example && make asan`, then run `./asan_demo` and identify the first bad line in the report.
- **14–22 min:** Run `make ubsan`, then `./ubsan_demo` and identify the undefined behavior.
- **22–27 min:** Compare sanitizer output to Valgrind: what is more direct, and what context is missing?
- **27–30 min:** Write a rule of thumb for when you would try ASan/UBSan first.

Deepen later: sanitizer options, LeakSanitizer, MemorySanitizer, and CI targets.

## Concepts to understand

- **Sanitizers are compile-time opt-in.** You rebuild with `-fsanitize=address`, etc. The compiler inserts instrumentation; the runtime library does the bookkeeping. No special launcher needed — you run the binary normally.
- **The main sanitizers:**
  - **AddressSanitizer (ASan):** heap overflows, stack overflows, use-after-free, use-after-return, use-after-scope, double-free. Roughly 2× overhead.
  - **UndefinedBehaviorSanitizer (UBSan):** signed overflow, out-of-range shifts, misaligned pointers, null deref, bad casts. Very low overhead; you can often ship with it.
  - **LeakSanitizer (LSan):** memory leak detector. Ships integrated with ASan on platforms that support it; Apple's ASan runtime does not support leak detection.
  - **MemorySanitizer (MSan):** tracks uninitialized reads. Only on Clang; requires instrumenting *all* dependencies, which is a real constraint.
  - **ThreadSanitizer (TSan):** data races — covered in Week 7.
- **ASan vs. Valgrind.** ASan is far faster and catches stack bugs Valgrind can't. Valgrind catches some things ASan can't (notably, requires no recompilation; handles arbitrary binaries). You want both in your toolbox.
- **You cannot mix some sanitizers.** ASan and MSan together don't work — pick one per build. ASan + UBSan + LSan happily coexist.
- **Shadow memory.** ASan maintains a "shadow" map with one byte per 8 bytes of application memory, encoding which bytes are poisoned (inaccessible). Knowing this helps you reason about what ASan can and can't see.

## Reading / watching

- AddressSanitizer paper (Serebryany et al., USENIX ATC 2012). Short, readable, classic.
- Clang documentation on each sanitizer (it's the canonical reference, even if you compile with GCC).
- "How ASAN works" — the LLVM blog and the Google Testing Blog both have good writeups.

## Core practice

### 1. Rebuild your Makefile with sanitizer targets

Add these to your Makefile:

```make
CFLAGS_ASAN   = -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer
CFLAGS_UBSAN  = -O2 -g -fsanitize=undefined -fno-sanitize-recover=undefined

asan: CFLAGS += $(CFLAGS_ASAN)
asan: LDFLAGS += -fsanitize=address,undefined
asan: $(TARGET)

ubsan: CFLAGS += $(CFLAGS_UBSAN)
ubsan: LDFLAGS += -fsanitize=undefined
ubsan: $(TARGET)
```

Why `-fno-sanitize-recover=undefined` — by default UBSan prints a warning and continues. You almost always want it to abort so tests fail, not silently pass.

### 2. Rerun last week's bug buffet under ASan

Take each of the bugs you wrote last week and run them under ASan instead of Valgrind. Compare:

- Speed — ASan is often 10× faster.
- Output — the shadow-memory diagrams show exactly which byte was poisoned and why.
- Stack coverage — ASan catches stack overflows Valgrind missed.

You'll start to develop intuition for which tool to reach for first.

### 3. Exercise UBSan

Write a program that does each of:

- Signed integer overflow (`INT_MAX + 1`)
- Left-shifting a negative number
- Dereferencing a misaligned pointer
- `(int *)0x1 -> deref` (null-ish pointer, misaligned, etc.)
- Reading past the end of an `enum`'s range

Build with UBSan and run. Note that UBSan is happy with most of these at compile time but *catches them at runtime* with a precise line number. This is information a compiler alone cannot give you.

### 4. LeakSanitizer

With ASan enabled, LSan runs at process exit. Introduce a deliberate leak and confirm the exit-time report. Practice the `LSAN_OPTIONS` environment variable for suppressions:

```
LSAN_OPTIONS=suppressions=./leaks.supp ./myprog
```

### 5. Options &amp; environment variables worth knowing

- `ASAN_OPTIONS=detect_leaks=1:abort_on_error=1:symbolize=1`
- `UBSAN_OPTIONS=print_stacktrace=1`
- `ASAN_OPTIONS=halt_on_error=0` — continue after error (useful in tests to see all failures at once)

Read the sanitizer docs for the full list — there are dozens of knobs, and a handful save real time.

### 6. Wire sanitizers into CI mentally

Think about this even if you don't have a CI pipeline right now:

- ASan build runs on every PR.
- UBSan runs on the nightly job (more time, more flags).
- Valgrind runs weekly, because it's slow but finds things the others miss.

Sketch this in a paragraph or two in your notes. You don't have to implement it — the goal is to internalize the layered defense.

## Stretch

- Try MSan (Clang only): `-fsanitize=memory`. Expect pain — you'll need libc++ or a clean build of all dependencies. Worth doing once so you understand the tradeoffs.
- Explore `libfuzzer` — structure-aware fuzzing integrated with sanitizers. Even a simple fuzz harness over a parser is a spectacular bug-finding tool.
- Read about `-fsanitize=cfi` (control-flow integrity) and `-fstack-protector-strong` — related compiler hardening features.

## Checkpoint

You can move to Week 7 when you can:

- Explain the differences between ASan, UBSan, LSan, and MSan, and when to reach for each.
- Rebuild a project under ASan+UBSan and run your test suite.
- Read an ASan report — including the shadow-memory lines — and point to the bug.
- Explain the tradeoffs between ASan and Valgrind and when you'd use each.
