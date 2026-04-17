# Week 9 — Logging, Tracing &amp; Observability

## Goal

Learn the tools and habits that let you debug *without* a debugger — often the only option on production machines, embedded targets, or anywhere a debugger is too heavy or too slow. Also: learn to write logs that help rather than hurt.

## Concepts to understand

- **`printf` debugging isn't shameful — but it is a skill.** Done well, structured, and paired with the right filters, logs are often the fastest path to insight. Done poorly, they're noise.
- **Structured logs** (key=value or JSON) are filterable and correlatable. Free-form text is not.
- **`strace` shows syscalls**, `ltrace` shows library calls. Both are indispensable for "what is this program actually doing at the OS boundary?" — especially for bugs at the interface between your code and the system.
- **`perf`** samples CPU activity with minimal overhead. `perf top`, `perf record` + `perf report`, and flamegraphs are how you see where time goes without rebuilding anything.
- **Dynamic tracing** — `bpftrace`, `eBPF`, or `dtrace` — lets you attach probes to running kernel and userspace code without modifying it. Once you've used it, nothing else feels the same.
- **Observability ≠ monitoring.** Monitoring answers "is the thing broken?" Observability answers "why is it broken, in a way we didn't anticipate?" The latter is what debugging needs.

## Reading / watching

- "Structured Logging" — multiple good blog posts; the content is short, the idea is simple, the practice matters.
- Brendan Gregg's site (brendangregg.com) — especially "Perf Examples" and "BPF Performance Tools." He is *the* reference on this material.
- `man strace` — read it. The `-f`, `-e`, `-c`, `-o`, and `-tt` flags alone are worth the time.

## Core practice

### 1. Rework your logging

If you've been using `printf(...)` for everything, try this structure instead. Write a small logging macro:

```c
#define LOG(level, fmt, ...) \
    fprintf(stderr, "time=%ld level=%s src=%s:%d " fmt "\n", \
            time(NULL), level, __FILE__, __LINE__, ##__VA_ARGS__)

LOG("info", "accepted_connection client_ip=%s fd=%d", ip, fd);
```

Key moves:

- A timestamp on every line, always.
- A level (`debug`/`info`/`warn`/`error`) — makes filtering trivial.
- Source location.
- Key=value pairs instead of prose where possible.
- One event per line. No multi-line prose. `grep`/`awk` become your debugger.

Now rerun a recent bug investigation with this logging style. Notice how much easier it is to filter to the exact lines you care about.

### 2. `strace` as a first-line tool

For any program behaving mysteriously — not crashing, just *wrong* — run it under `strace` first:

```
strace -f -tt -o trace.log ./myprog
```

Then search the log for `open`, `read`, `write`, `connect`, `futex`. You'll often see the bug directly — "oh, it's reading the wrong config file" or "it never opens the socket" — without ever launching a debugger.

Practice deliberately:

- A program that reads a config file — use `strace -e openat` to see every file it tries to open.
- A program that talks to the network — use `strace -e network` to see its socket behavior.
- A program that hangs — attach with `strace -p PID` to see what syscall it's blocked in.

### 3. `ltrace`

Same idea, one level up — shows dynamic library calls. Useful for understanding what your program is doing with libc or third-party libraries. Slower and less robust than `strace`, but a good second tool in the belt.

### 4. `perf` basics

```
perf stat ./myprog              # cycles, IPC, cache misses
perf top                        # live, who's using the CPU
perf record -g ./myprog         # record call graphs
perf report                     # interactive
```

Generate a flamegraph once — any of the FlameGraph scripts from Brendan Gregg's repo. Seeing a flamegraph of your own code is a formative experience.

Note: `perf` is primarily a *performance* tool, but performance regressions often start as debugging mysteries ("why is this slow?"). The line between debugging and profiling is thinner than textbooks suggest.

### 5. Dynamic tracing — a small taste

Install `bpftrace` (Linux only). Try:

```
# count syscalls per process
bpftrace -e 'tracepoint:raw_syscalls:sys_enter { @[comm] = count(); }'

# histogram of read() sizes
bpftrace -e 'tracepoint:syscalls:sys_enter_read { @ = hist(args->count); }'
```

You don't need to become a bpftrace expert. You just need to know the tool exists so next time you face an observability puzzle in production, it's on your list.

### 6. Core practice exercise

Take the multi-threaded program from Weeks 7/8. Remove all sanitizers. Rebuild as a normal release binary. Now, using *only* structured logging and `strace`, diagnose a bug you planted — e.g., a race that sometimes drops messages. Did you find it? How long did it take? This is the skill the week is about.

## Stretch

- Build a simple `rsyslog`/`journald` setup and ship your logs there. Experience the difference between local logs and centralized logs.
- Try `dtrace` on macOS or FreeBSD (it's available, often underused). Compare the experience to bpftrace.
- Read Kent Beck's "Tidy First?" chapter on logs — specifically the section on logs as a design tool.

## Checkpoint

You can move to Week 10 when you can:

- Write a structured log line that would survive grep/awk triage a week later.
- Diagnose a broken program's behavior using `strace` as the primary tool.
- Run `perf record` + `perf report` on a program and identify the hottest function.
- Describe a scenario where dynamic tracing (bpftrace/eBPF) is the right tool and why.
