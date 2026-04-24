# Week 3 — Advanced GDB

## Goal

Unlock the parts of GDB that separate "tourist" users from power users: watchpoints, scripting, pretty-printing, and — the most transformative of all — reverse execution.

## 30-minute pass

- **0–5 min:** Read the watchpoint concept and the warning about watching `*ptr`.
- **5–15 min:** `cd example && make`, run `./watchpoint_demo`, then open it in GDB.
- **15–23 min:** Use `break main`, `run`, `watch secret`, and `continue` until GDB shows who writes the suspicious value.
- **23–27 min:** If `rr` is installed, run `make rr` and `make replay`, then try `reverse-continue`. If not, repeat the watchpoint pass and focus on the evidence chain.
- **27–30 min:** Add one useful `.gdbinit` setting or write a journal note answering: "Who changed the value, and how did I prove it?"

Deepen later: Python pretty-printers, custom commands, and remote debugging.

## Concepts to understand

- **Watchpoints stop on state change, not location.** `watch x` stops the program whenever `x` is written. This is how you find "who set this variable to 7?" bugs in seconds instead of hours.
- **Hardware vs. software watchpoints.** Hardware watchpoints (x86 has 4) are fast. Software watchpoints single-step every instruction and are glacial — GDB will warn you when it falls back to them.
- **Pretty printers** turn your opaque structs into readable output. GDB ships with pretty-printers for glibc types; you can write your own in Python.
- **GDB's Python API** lets you automate almost anything — custom commands, new pretty-printers, hooks that fire on stops.
- **Reverse execution** means stepping *backwards* in time. Native GDB record mode is slow but works; the `rr` tool from Mozilla is production-quality and fast enough for real use.

## Reading / watching

- *Debugging with GDB*, chapters on watchpoints, Python scripting, and process record.
- Mozilla's `rr` documentation — especially the "Usage" and "Chaos mode" pages.
- Greg Law's follow-up talk "More GDB tips."
- A few examples of `.gdbinit` and Python pretty-printers from real projects (glibc's, CPython's).

## Core practice

### 1. Watchpoints

Write a program where a global or struct field gets unexpectedly modified. Hunt it with:

- `watch var` — break on write
- `rwatch var` — break on read
- `awatch var` — break on either
- Watch on an expression, e.g. `watch *ptr` or `watch buf[5]`

Things to notice:

- A watchpoint on a local variable goes out of scope when the function returns — GDB deletes it automatically.
- Watching a dereferenced pointer watches the *current target*, not the pointer itself. If the pointer gets reassigned, you're now watching stale memory. Understand this — it catches everyone once.

### 2. Pretty printers

Pick a small struct from your code — a linked list node, an intrusive hash table entry, something with a few fields and a pointer. Write a Python pretty-printer for it:

```python
# my_printers.py
import gdb

class NodePrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return f"Node(value={self.val['value']}, next={self.val['next']})"

def lookup(val):
    if str(val.type) == 'struct node':
        return NodePrinter(val)
    return None

gdb.pretty_printers.append(lookup)
```

Load it: `source my_printers.py`. Now `p some_node` uses your formatter.

### 3. Custom commands in Python

Write a GDB command that, say, dumps every element of your linked list:

```python
class PrintList(gdb.Command):
    def __init__(self):
        super().__init__("plist", gdb.COMMAND_USER)
    def invoke(self, arg, from_tty):
        node = gdb.parse_and_eval(arg)
        while int(node) != 0:
            print(node.dereference()['value'])
            node = node.dereference()['next']
PrintList()
```

Now `plist head` walks the list. For anything larger than a toy program, small commands like this pay for themselves in minutes.

### 4. Reverse debugging — the headline skill

If you remember one thing from the whole curriculum, let it be this: *you can step backwards*.

Install `rr` (Linux, x86-64 or aarch64):

```
rr record ./my_program some args
rr replay
```

Inside `rr replay` you get a normal GDB prompt, but now `reverse-continue`, `reverse-next`, `reverse-step`, and `reverse-finish` work. The classic workflow:

1. Run until the crash.
2. In the replay, `continue` — you land at the crash.
3. `watch bad_var` then `reverse-continue` — GDB travels back to the exact moment `bad_var` got its bad value.

Practice this at least three times on programs of your own. The first time it works, it will feel like cheating.

If you can't use `rr`, try GDB's built-in `target record-full` — same idea, much slower, single-threaded only.

### 5. `.gdbinit` hygiene

Start a real `.gdbinit`. Recommended minimum:

```
set history save on
set history size 10000
set print pretty on
set print array on
set print array-indexes on
set pagination off
set confirm off
```

Add aliases and macros as you find yourself repeating commands. Keep it small — a `.gdbinit` that does magic is a `.gdbinit` that confuses future-you.

## Stretch

- Read the source of a well-known pretty-printer package (e.g., `libstdc++`'s Python printers).
- Experiment with `rr`'s chaos mode — it randomizes thread scheduling, shaking out races you'd never hit otherwise.
- Try remote debugging: `gdbserver` on one machine, `gdb` connecting from another. Useful for embedded work or debugging inside Docker containers.

## Checkpoint

You can move to Week 4 when you can:

- Use `watch`, `rwatch`, and `awatch` correctly, and explain why watching `*ptr` is fragile.
- Write a small Python pretty-printer for a struct of your own.
- Record and replay a program with `rr`, then use `reverse-continue` with a watchpoint to find the moment a bad value was written.
- Point to your working `.gdbinit`.
