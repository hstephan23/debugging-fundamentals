# Week 2 — GDB Fundamentals

## Goal

Get fluent in everyday GDB: start a program, stop at the right place, inspect what's happening, and step through to understand it. By the end of the week, GDB should feel like a natural tool — not something you look up every command for.

## 30-minute pass

- **0–5 min:** Skim the command table in Core practice section 1.
- **5–18 min:** `cd example && make`, then run `gdb ./fib`. Use `break fib`, `run 10`, `bt`, `info args`, `info locals`, and `finish`.
- **18–24 min:** Set one conditional breakpoint, such as `break fib if n == 3`, and confirm it stops only when expected.
- **24–27 min:** Try TUI mode with `Ctrl-x a` or note why your terminal does not support it well.
- **27–30 min:** Write the five commands you actually used and what each revealed.

Deepen later: attaching to `sleeper`, silent breakpoint commands, and editor-integrated debugging.

## Concepts to understand

- **Breakpoints vs. watchpoints vs. catchpoints.** This week we focus on breakpoints — stopping at a *location*. (Watchpoints on *values* come next week.)
- **The stack frame.** Every function call pushes a frame; GDB navigates between them with `up`, `down`, and `frame N`. A crash is almost always investigated by walking the stack.
- **Symbols and debug info.** GDB can only show you what's in the binary. `-g3` embeds the most. Stripped binaries give you almost nothing.
- **Running vs. attached.** You can launch a program under GDB (`gdb ./a.out`) or attach to a running one (`gdb -p PID`). Attaching matters for server processes and daemons.
- **TUI mode.** GDB has a terminal UI (`Ctrl-x a` or `gdb -tui`) that shows source alongside the prompt. Once you learn it, you rarely go back.

## Reading / watching

- *Debugging with GDB* (the GNU manual), chapters 1–8. Read as reference, not cover to cover.
- Greg Law's talk "Give me 15 minutes and I'll change your view of GDB." Short, motivating, dense.
- `help` inside GDB — it's genuinely useful. `help running`, `help stack`, `help data`.

## Core practice

### 1. Learn the minimum vocabulary cold

Practice these until you don't think about them:

| Command | Short | Does |
|---|---|---|
| `run` | `r` | start the program |
| `break main` / `break file.c:42` / `break func` | `b` | set a breakpoint |
| `continue` | `c` | resume until next stop |
| `next` | `n` | next line, stepping over calls |
| `step` | `s` | next line, stepping into calls |
| `finish` | `fin` | run until current frame returns |
| `print expr` | `p` | evaluate and print |
| `info locals` / `info args` | | inspect current frame |
| `backtrace` | `bt` | show the call stack |
| `frame N` | `f` | switch to frame N |
| `list` | `l` | show source around current line |
| `quit` | `q` | exit |

Also learn: `display EXPR` (auto-print on every stop), `info breakpoints`, `delete N`, `disable N`, `enable N`.

### 2. Walk through a small program

Grab any small C program you have — or write a 50-line recursive one, like a Fibonacci with memoization. Set a breakpoint on the recursive call. Step through. Practice:

- `bt` at various depths and confirming what frame you're in
- `p` on local variables, struct fields, and expressions like `p arr[i] * 2 + 1`
- `info locals` vs. `info args` in the current frame
- `finish` to bubble back up one level

### 3. Use breakpoints realistically

Practice:

- Breakpoint on a line: `break utils.c:87`
- Breakpoint on a function: `break parse_header`
- Conditional breakpoint: `break utils.c:87 if n == 42`
- Ignore count: break but only stop on the 100th hit — `ignore 1 99`
- Commands attached to a breakpoint: automatically print state and continue

```
(gdb) break foo
(gdb) commands
> silent
> printf "foo called with x=%d\n", x
> continue
> end
```

That pattern — "break, print, continue" — is one of the most useful debugging tricks you'll learn all month. It's `printf` debugging without recompiling.

### 4. Learn TUI mode

Launch with `-tui` or press `Ctrl-x a`. Learn:

- `Ctrl-x 2` — cycle layouts (source, asm, split)
- `Ctrl-l` — redraw (you will need this)
- Arrow keys to scroll source independently
- `focus cmd` / `focus src` — move cursor between panes

If TUI feels clunky on your terminal, try `gdbgui` or the VS Code debugger — they wrap GDB with a nicer interface.

### 5. Attach to a running process

Write a program that sleeps in an infinite loop. Launch it. From another terminal, `gdb -p $(pgrep your_prog)`, poke around, and detach cleanly with `detach` (not `quit` — that would kill the process).

If you hit "ptrace: Operation not permitted," check `/proc/sys/kernel/yama/ptrace_scope`. On most Linux distros, setting it to 0 (temporarily) allows attaching to your own processes.

## Stretch

- Explore `info registers`, `x/20xw $sp`, and examining raw memory. You don't need it often, but you need to *not be afraid of it*.
- Try GDB inside your editor (VS Code's C/C++ extension, or `M-x gud-gdb` in Emacs). Know which tool you prefer, and why.
- Read about `.gdbinit` and start a minimal one — set your history size, enable pretty-printing, load your favorite helper commands.

## Checkpoint

You can move to Week 3 when you can, without referring to notes:

- Start a program in GDB, set a breakpoint at a specific line, run to it, and inspect locals.
- Walk up and down the stack and explain what `frame N` is showing you.
- Set a conditional breakpoint that fires only on a specific input.
- Attach to and detach from a running process without killing it.
- Demonstrate "silent breakpoint with commands" to instrument a running program.
