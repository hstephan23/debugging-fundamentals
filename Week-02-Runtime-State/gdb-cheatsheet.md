# GDB Cheat Sheet — Week 2

A pocket reference you can keep open while you're still building muscle memory.

## Starting and stopping

| | |
|---|---|
| `gdb ./prog`                | launch |
| `gdb --args ./prog a b c`   | launch with program arguments |
| `gdb -p PID`                | attach to running process |
| `gdb ./prog ./core`         | postmortem from a core file |
| `run` / `r`                 | start (or restart) |
| `kill`                      | terminate the inferior |
| `detach`                    | detach without killing (for attached processes) |
| `quit` / `q`                | exit GDB |

## Breakpoints

| | |
|---|---|
| `break main`                | break on function entry |
| `break file.c:42`           | break at a line |
| `break func if n == 42`     | conditional |
| `ignore 1 99`               | ignore breakpoint #1 for 99 hits |
| `info breakpoints` / `i b`  | list |
| `disable 2` / `enable 2`    | toggle by number |
| `delete 2`                  | remove |
| `tbreak` / `tb`             | one-shot breakpoint |

### "Silent log" pattern (printf without recompiling)

```
(gdb) break parse_header
(gdb) commands
> silent
> printf "parse_header called: len=%d buf=%p\n", len, buf
> continue
> end
```

## Execution control

| | |
|---|---|
| `continue` / `c`            | resume |
| `next` / `n`                | step over |
| `step` / `s`                | step into |
| `finish` / `fin`            | run until current frame returns |
| `until 87` / `u 87`         | run until line 87 in the current frame |
| `stepi` / `si`              | instruction-level step |

## Inspecting state

| | |
|---|---|
| `backtrace` / `bt`          | stack trace |
| `bt full`                   | stack + locals in each frame |
| `frame N` / `f N`           | switch frames |
| `up` / `down`               | move one frame |
| `info args`                 | args of current frame |
| `info locals`               | locals of current frame |
| `info registers`            | CPU registers |
| `print expr` / `p expr`     | evaluate and print |
| `p/x val`                   | print in hex |
| `display expr`              | auto-print on every stop |
| `list` / `l`                | show source around here |
| `x/20xw $sp`                | examine 20 hex words at $sp |

## TUI mode

| | |
|---|---|
| `Ctrl-x a`                  | toggle TUI |
| `Ctrl-x 2`                  | cycle layouts |
| `Ctrl-l`                    | redraw |
| `focus cmd` / `focus src`   | move keyboard focus |

## Handy

| | |
|---|---|
| `set pagination off`        | stop asking "--More--" |
| `set print pretty on`       | indent structs |
| `set logging on`            | write session to `gdb.txt` |
| `help <topic>`              | it's actually good |
