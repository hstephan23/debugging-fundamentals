# Debugging — 10-Week Learning Plan

A self-directed curriculum for becoming a confident, methodical debugger — with a sharp focus on C, and a broader focus on debugging as a discipline that transfers to any language.

## Who this plan is for

- You're already comfortable writing C: you understand pointers, structs, and basic memory management, and you've compiled programs with `gcc` or `clang`.
- You want to move beyond `printf` debugging and build real muscle memory with GDB, sanitizers, and postmortem tools.
- You want to treat debugging as a skill — not a reactive panic — and develop habits that make bugs rarer and easier to find when they do appear.

## Time commitment

Plan assumes **5–8 hours/week** — roughly one evening of reading/watching plus a weekend practice session. If you only have 2 hours one week, do the **Core practice** section and skip the **Stretch** items.

## What you'll be able to do at the end

- Drop into any crashed C program, load a core dump, and narrow the root cause to a specific line within minutes.
- Diagnose memory bugs (leaks, use-after-free, buffer overflows) with both Valgrind and AddressSanitizer, and know when to reach for which.
- Debug multithreaded programs — find data races with ThreadSanitizer, deadlocks with Helgrind, and inspect live threads in GDB.
- Write logs and instrumentation that actually help future-you instead of cluttering the output.
- Apply a reproducible debugging methodology (observe → hypothesize → isolate → verify) under pressure.
- Write code that's *easier* to debug in the first place: assertions, invariants, defensive compilation flags, and meaningful error handling.

## Tools you'll install

Most weeks assume a Linux environment (or WSL2 on Windows, or macOS with some adjustments). If you're on macOS, note that Valgrind support is limited on recent versions — use a Linux VM, Docker container, or cloud box for weeks 5 and 8.

Core toolchain — install in Week 1:

- `gcc` and/or `clang` (12+ recommended for full sanitizer support)
- `gdb` (10+ recommended)
- `make`, `cmake`
- `valgrind`
- `strace`, `ltrace`
- `perf` (linux-tools package)
- `rr` (reverse debugger) — optional but highly recommended for Week 3
- An editor with a GDB integration: VS Code with the C/C++ extension, CLion, or Emacs + `gud`

## Weekly structure

Each week's file follows the same shape so you can pace yourself:

1. **Goal** — one sentence describing what you should walk away with.
2. **Concepts** — the ideas to understand before touching the tools.
3. **Reading / watching** — a short list, not an exhaustive survey.
4. **Core practice** — the exercises that actually build skill. Do these.
5. **Stretch** — optional deeper dives for weeks you have extra time.
6. **Checkpoint** — a short self-assessment. If you can't pass it, loop back before moving on.

## The 10 weeks at a glance

| Week | Theme | Primary tools |
|------|-------|---------------|
| 1 | Debugging methodology &amp; toolchain setup | `gcc -g`, `clang`, `make` |
| 2 | GDB fundamentals | `gdb` |
| 3 | Advanced GDB: watchpoints, scripting, reverse debugging | `gdb`, `rr` |
| 4 | Core dumps &amp; postmortem debugging | `gdb`, `coredumpctl` |
| 5 | Memory bugs with Valgrind | `valgrind memcheck` |
| 6 | Sanitizers: ASan, UBSan, LSan, MSan | `-fsanitize=...` |
| 7 | Concurrency I — data races | pthreads, `ThreadSanitizer` |
| 8 | Concurrency II — deadlocks &amp; live debugging | `helgrind`, `gdb` threads |
| 9 | Logging, tracing, observability | `strace`, `ltrace`, `perf`, structured logs |
| 10 | Capstone &amp; writing debuggable code | everything |

## Folder layout

Each week lives in its own directory with a `README.md` (the plan) and an `example/` subdirectory that holds the practice code:

```
Debugging/
├── README.md                         (this file)
├── Week-01-Foundations/
│   ├── README.md                     (the plan for the week)
│   ├── bug-journal.md                (your living notes)
│   └── example/                      (Makefile + C sources)
├── Week-02-GDB-Fundamentals/
│   ├── README.md
│   ├── gdb-cheatsheet.md
│   └── example/
├── Week-03-Advanced-GDB/
│   ├── README.md
│   └── example/
├── Week-04-Core-Dumps/
│   ├── README.md
│   └── example/
├── Week-05-Valgrind/
│   ├── README.md
│   └── example/                      (8-program "bug buffet")
├── Week-06-Sanitizers/
│   ├── README.md
│   └── example/
├── Week-07-Concurrency-1/
│   ├── README.md
│   └── example/
├── Week-08-Concurrency-2/
│   ├── README.md
│   └── example/
├── Week-09-Logging/
│   ├── README.md
│   └── example/
└── Week-10-Capstone/
    ├── README.md
    ├── bug-journal-template.md
    ├── playbooks.md                  (five debugging playbooks)
    └── example/                      (Makefile.template, debuggable.h)
```

Each `example/` directory contains a `Makefile` and at least one working C program — deliberately buggy in most cases, since the point is to practice diagnosing. `cd` into it and run `make` (or `make asan`, `make tsan`, `make valgrind`, etc., depending on the week) to build.

## How to use this plan

- **Do the exercises.** You cannot learn debugging by reading about debugging. Every week has hands-on practice — treat it as the main event.
- **Keep a bug journal.** A single text file where you record, for each bug you investigate: the symptom, what you thought it was, what it actually was, and what tipped you off. After a few weeks this becomes the most valuable artifact in the whole curriculum.
- **Don't skip Week 1.** The methodology material looks soft next to the tooling, but it's what separates people who *know* GDB from people who can actually debug.
- **It's fine to fall behind.** Miss a week, do it the week after. The sequence matters more than the calendar.

Good luck — and remember that every bug you fix makes the next one easier.
