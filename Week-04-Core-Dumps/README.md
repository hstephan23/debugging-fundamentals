# Week 4 — Core Dumps &amp; Postmortem Debugging

## Goal

Learn to investigate crashes you couldn't witness live. By the end of the week, a core dump from a server crash at 3 AM should be something you can load, triage, and root-cause from your laptop the next morning — without a reproducer.

## 30-minute pass

- **0–5 min:** Read the concepts on core files, debug symbols, and stack frames.
- **5–12 min:** `cd example && make`, then enable cores with `ulimit -c unlimited`.
- **12–18 min:** Run `./crash "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"` and locate the generated `core` or `core.*` file. If your system intercepts cores, use `coredumpctl list`.
- **18–26 min:** Open `gdb ./crash ./core`, `gdb ./crash ./core.*`, or `coredumpctl gdb crash`, then use `bt`, `frame N`, `info args`, and `info locals`.
- **26–30 min:** Journal the crash site, the likely root cause, and the one stack frame that proved it.

Deepen later: split debug info, corrupted stacks, and matching cores to logs.

## Concepts to understand

- **A core dump is a snapshot of the process's memory at the moment it died.** Given the dump, the original binary, and debug info, GDB can reconstruct almost the entire crash scene: stack, locals, globals, heap.
- **Core files are disabled by default on many systems.** `ulimit -c unlimited` enables them for the shell; `/proc/sys/kernel/core_pattern` controls where they go. On modern Linux, `systemd-coredump` intercepts and stores them — retrieve with `coredumpctl`.
- **Matching binary + matching debug info is non-negotiable.** If you loaded a core against a binary that's been rebuilt, backtraces will lie to you. Ship with split debug info (`.debug` files) and archive them.
- **Separate debug info** (`objcopy --only-keep-debug`, `strip`, then `add-symbol-file` or `set debug-file-directory`) is the production pattern — lets you ship small stripped binaries while keeping full debug info available for postmortem.
- **A crashed process tells you *where* it died; your job is to work out *why*.** That usually means walking the stack, inspecting arguments and locals in each frame, and correlating with the code.

## Reading / watching

- `man core`, `man 5 core`, `man coredumpctl`.
- The Linux kernel documentation on `core_pattern`.
- GDB manual chapters on "Files" (especially separate debug info) and "Examining Memory."
- Julia Evans' zine/article on debugging with core dumps — short and friendly.

## Core practice

### 1. Enable core dumps on your system

```bash
ulimit -c unlimited              # enable for this shell
cat /proc/sys/kernel/core_pattern # see where they go
```

If the pattern is a pipe (`|/usr/lib/systemd/systemd-coredump ...`), you're using systemd-coredump — try `coredumpctl list`, `coredumpctl info`, `coredumpctl gdb`. Otherwise you'll find a `core` file or `core.PID` in the working directory.

Write a program that deliberately segfaults (e.g., deref a null pointer). Run it. Confirm a core file appears. Load it:

```
gdb ./a.out ./core
```

Run `bt` and confirm you're looking at the crash location.

### 2. Investigate a realistic crash

Write a small program with a **plausible** bug:

- a function that calls `strcpy` into a fixed-size buffer,
- a caller that occasionally passes an overlong string,
- a third function that uses the buffer afterwards.

Run until it crashes. Load the core. Don't just stop at `bt` — practice:

- `frame N` into each function along the stack
- `info args` and `info locals` in each
- `p *argv` style dereferences to see what inputs the program had
- `x/s buffer` to see the raw contents of suspicious memory

Write up your findings in the bug journal as if you were filing a post-mortem report: what crashed, where, why, and what you'd change to prevent it.

### 3. Separate debug info

Practice the production pattern:

```bash
gcc -g -O2 -o myprog main.c
objcopy --only-keep-debug myprog myprog.debug
strip --strip-debug myprog
objcopy --add-gnu-debuglink=myprog.debug myprog
```

Confirm:

- `file myprog` shows it's stripped.
- GDB still finds debug info via the `.gnu_debuglink` section if `myprog.debug` is in the same directory or a `.debug/` subdirectory.

Now imagine archiving `myprog.debug` somewhere alongside every build. Three months from now, a core arrives — you fetch the matching `.debug` file and you're back in business.

### 4. Learn to read a stack that's been corrupted

Sometimes the crash scribbled over the stack and `bt` shows `??` for frames. Learn the fallbacks:

- `info registers` — what's in `rbp`/`rsp`/`rip` at the moment of death?
- `x/32xw $rsp` — raw stack bytes, often reveals strings, pointers, or recognizable values
- `disassemble $rip` — what instruction caused the signal?
- Stack backtrace with `bt full` to see any locals GDB can still reconstruct

This is uncomfortable territory the first time. Staying calm and reading the raw state is the skill.

### 5. Correlate core with logs

Have your program write a log line including its PID before the crash. Then correlate the core (`coredumpctl info`) with the log: same PID, same timestamp, same host. In a real incident, this chain of evidence is what lets you tie "the crash" to "the user request that triggered it."

## Stretch

- Set up a minimal crash-reporting pipeline of your own: a wrapper script that, on crash, moves the core to a dated directory with the binary hash, and writes a small manifest.
- Read about signal handlers and the `SIGSEGV`/`SIGBUS` distinction. Write a signal handler that prints a backtrace (using `backtrace()` from `execinfo.h`) before exiting.
- Look up `gcore` — it takes a core dump of a *running* process without killing it. Useful for "this process is wedged, grab a snapshot before I restart it."

## Checkpoint

You can move to Week 5 when you can:

- Enable core dumps, crash a program deliberately, and load the core in GDB.
- Walk a stack in a core and explain what each frame did, based on locals and args.
- Set up separate debug info and load it correctly.
- Describe how you'd investigate a core that arrived without a reproducer, step by step.
