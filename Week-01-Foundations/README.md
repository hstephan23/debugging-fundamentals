# Week 1 — Foundations &amp; Debugging Methodology

## Goal

Build a mental model of debugging as a disciplined, reproducible process — and get your C toolchain into a state where it helps you instead of fighting you.

## 30-minute pass

- **0–5 min:** Read the first three concepts: hypothesis, reproducibility, and bisection.
- **5–15 min:** `cd example`, then run `make debug` and `make release`.
- **15–22 min:** Run both binaries with `make run-debug` and `make run-release`. Note whether optimization changes the symptom.
- **22–27 min:** Inspect the Makefile flags and identify which ones help debugging versus release behavior.
- **27–30 min:** Start a bug-journal entry with: symptom, first hypothesis, evidence, and next experiment.

Deepen later: the manual input-reduction exercise, `git bisect`, and the undefined-behavior reading.

## Concepts to understand

- **Debugging is science, not divination.** You observe a symptom, form a hypothesis, design an experiment to confirm or refute it, and iterate. Zeller's "Why Programs Fail" frames this as *scientific method for programs*.
- **The two hardest parts are usually (1) reproducing the bug and (2) narrowing the search space.** Tools help with step 2. Methodology helps with both.
- **Bisection is your most powerful generic tool.** Whenever the search space is too large, cut it in half. This applies to code (git bisect), inputs (reduce the failing test case), and state (checkpoint + compare).
- **"It works on my machine" usually means a hidden input differs.** Treat environment, timing, data, and compiler flags as inputs to the program.
- **Compiler flags change behavior.** `-O0` vs `-O2` can turn a bug on or off. Undefined behavior (UB) gives the compiler permission to do almost anything. Your first job is to build in a mode where the compiler tells you the truth.

## Reading / watching

- *Why Programs Fail* (Andreas Zeller) — Chapter 1 ("How Failures Come to Be") and Chapter 4 ("Reproducing Problems"). If you only read one book from this plan, read this one.
- "Rubber Duck Debugging" — short post, but worth internalizing.
- John Regehr's blog post "A Guide to Undefined Behavior in C and C++" (all three parts).
- GCC manual section on "Options That Control Optimization" — skim, don't memorize.

## Core practice

### 1. Set up a clean debug build

Create a small C project (one `main.c`, one `utils.c`, a `Makefile`). In the Makefile, create two build modes:

```make
CFLAGS_DEBUG = -O0 -g3 -Wall -Wextra -Wpedantic -Wshadow -Wconversion \
               -fno-omit-frame-pointer -fno-common -D_FORTIFY_SOURCE=2

CFLAGS_RELEASE = -O2 -g -Wall -Wextra -DNDEBUG
```

Verify that:

- `make debug` produces an unoptimized binary that you can step through line by line.
- Every warning you see gets fixed, not silenced. This is a habit worth forming now.

### 2. Write a bug, then diagnose it

Write a function that sums the elements of an array, then deliberately introduce an off-by-one in the loop bound. Compile with `-O0` and `-O2`. Run both. Notice how `-O2` may produce different (sometimes misleading) symptoms.

Now diagnose it *without a debugger*. Use only: re-reading the code, adding assertions, and printing state at chosen points. Write down in your bug journal:

- What was your first hypothesis?
- What experiment ruled it out?
- How long did it take?

The point is to feel how much effort "just look at it" takes, so you appreciate what tools give you in later weeks.

### 3. Practice bisection on inputs

Take a program (yours or an open-source one) that has a crashing input of reasonable size — a malformed JSON file, say, or a corrupt image. Using only manual editing, reduce the input to the smallest version that still crashes. This is called *test-case reduction* and is a core skill. Tools like `creduce` automate it, but doing it by hand once builds intuition.

### 4. Start your bug journal

Create `bug-journal.md`. For every non-trivial bug you investigate from now on — whether from this curriculum or from real work — write down:

- **Symptom:** what you observed
- **Hypothesis:** what you thought was wrong
- **Reality:** what was actually wrong
- **Tell:** what piece of evidence would have pointed you to the real cause faster

## Stretch

- Read Brian Kernighan's "The Practice of Programming," Chapter 5 ("Debugging"). Old book, still excellent.
- Learn `git bisect` on a real repo: introduce a bug in an old commit of your own project, then bisect to find it.
- Read about "Delta Debugging" — the algorithm behind `creduce`.

## Checkpoint

You can move to Week 2 when you can:

- Explain the difference between `-O0 -g` and `-O2 -g` builds, and why both matter.
- Name three compiler warnings you now enable by default, and what each catches.
- Describe the scientific method version of debugging in your own words, without looking.
- Point to your first few bug journal entries.

If any of those feels shaky, spend another day on Week 1 — the rest of the plan leans on these foundations.
