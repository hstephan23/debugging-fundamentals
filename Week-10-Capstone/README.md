# Week 10 — Capstone &amp; Writing Debuggable Code

## Goal

Consolidate everything with a substantial bug hunt, then turn the lens outward: the habits, idioms, and structural choices that make code *easier to debug in the first place*. The best debugger is the one you didn't have to use.

## 30-minute pass

- **0–5 min:** Pick one playbook from `playbooks.md`: crash, hang, memory corruption, concurrency, or slowness.
- **5–12 min:** Choose one small reproducer from the earlier weeks that matches the playbook.
- **12–23 min:** Run the first tool the playbook recommends and capture the strongest piece of evidence.
- **23–27 min:** Sketch the root cause or, if it is not proven yet, the next experiment that would prove or disprove it.
- **27–30 min:** Fill one entry in `bug-journal-template.md` as a mini post-mortem.

Deepen later: one full capstone option and the debuggable-code checklist.

## Concepts to understand

- **Debuggability is a design attribute.** Error handling, assertions, invariants, logging hooks, deterministic tests — these aren't just "nice to have," they're what turns a six-hour bug hunt into a six-minute one.
- **Assertions are free documentation that also fire at runtime.** An invariant written in English is a comment. An invariant written as `assert(x != NULL)` is also enforced.
- **Crash early, crash loudly.** Detecting a corrupted invariant at the moment it happens beats detecting its consequences three modules later.
- **Reproducibility is the biggest multiplier.** A bug you can reproduce on demand is a bug you can fix. Most debugging effort in the real world goes into *getting* a reproducer — seeds, logs, captures, core dumps.
- **Writing up a bug is part of fixing it.** A post-mortem style writeup — even for a small bug — forces you to articulate what actually happened, and helps the next person (often future-you).

## Reading / watching

- John Regehr, "Write Fuzzable Code" — short, opinionated, transferable.
- Jim Roskind &amp; others, "The Sane Way to Use `assert`" — assertions are surprisingly controversial; read both sides.
- Your own bug journal from the last nine weeks. Read it end-to-end. Look for patterns.

## Capstone project (bulk of the week)

Pick one and commit seriously:

### Option A — "Inherited codebase" bug hunt

Fork an open-source C project of modest size (say, 5k–50k LOC) — examples: `sqlite`, `musl`, `redis`, `tmux`, `curl`, or a smaller tool like `jq`. Pick a real open bug from its issue tracker that looks tractable. Reproduce it locally. Use every tool you've learned — GDB, sanitizers, logs — to diagnose root cause. Don't just read code; drive *from* the bug back to its source.

Write up what you found as if it were a post-mortem:

- Symptom
- Reproducer
- Investigation (what you tried, what it told you)
- Root cause
- Proposed fix (you don't have to land it — but sketch it)

### Option B — "Planted bugs" gauntlet

Take a program you've written. Hand it to a friend (or use a random seed to generate mutations) to introduce 5–10 bugs: some memory, some concurrency, some logic, some performance. Don't look at what they changed. Run your debugging playbook on each as if it were a production incident, using the appropriate tool for each class of bug. Time yourself. Note which kinds of bugs you're fast at and which you're slow at.

### Option C — Build a "debuggable by construction" project from scratch

Pick a small system (a line-based HTTP server, a shell, a key-value store) and build it end-to-end with every debuggability practice baked in from the start:

- Two build modes (debug, release with separate debug info archived).
- Sanitizer CI target.
- Valgrind CI target.
- Structured logging with runtime log level.
- Assertions on every non-trivial invariant.
- A deterministic test harness; a fuzz harness; a stress-test harness.
- Per-request/operation context that flows through logs.

Use it. Deliberately break it. Observe how much faster you find things.

## Writing debuggable code — a checklist

Distill this into a note you keep and reread periodically:

### Defensive compilation

- `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` by default; fix every warning.
- `-fsanitize=address,undefined` in dev and CI.
- `-D_FORTIFY_SOURCE=2 -fstack-protector-strong` in release.
- Ship with debug info, strip it from the binary, archive the `.debug` file.

### Error handling

- Every function that can fail should return a status; every caller should handle it.
- Don't silently swallow errors. Log them, even at `debug` level.
- Validate inputs at public boundaries. Trust internal invariants (and assert them).
- Use `goto cleanup;` style for resource cleanup in C — it's a feature, not a smell.

### Assertions &amp; invariants

- Assert preconditions on public functions.
- Assert postconditions on complex returns.
- Assert invariants inside long functions.
- Keep assertions on in production if you can afford it. `assert()` aborts on failure, which is loud but informative — usually better than silent corruption.
- `static_assert` for compile-time invariants.

### Structured data and logs

- Every request/operation carries an ID. That ID appears in every log line.
- Key=value logs, one line per event.
- A way to raise the log level at runtime (signal or config reload) so you can "turn on debug" without restart.

### Testability

- Pure functions where possible — inputs in, outputs out, no globals.
- Inject dependencies (time, randomness, file I/O) so tests can control them.
- A deterministic mode for your RNG, scheduler, clocks.
- Tests fast enough to run on every save. Slow tests get skipped; skipped tests rot.

### Reproducibility

- Tests log their seed. A failing test tells you the exact seed to replay.
- Crash reports capture: binary hash, log tail, core dump, system info.
- A one-liner to reproduce: `./run --seed=12345 --input=./fixtures/bug23`.

## Retrospective (the actual last thing you do)

Before closing out the curriculum, write a retrospective in your bug journal:

- Which week changed your practice the most?
- Which tool did you think you'd use constantly but don't?
- Which one surprised you?
- What will you build into your default setup (editor config, `.gdbinit`, Makefile template) going forward?
- What will you skip until you actually need it again?

Then file the journal somewhere permanent. A year from now it will tell you things no blog post can.

## Checkpoint — you're done when

- Your capstone project has a written post-mortem (for Option A/B) or a README demonstrating its debuggability features (Option C).
- You have a personal debugging toolkit: `.gdbinit`, Makefile template with sanitizer and Valgrind targets, logging macros, bug-journal template.
- You can walk someone else through your end-to-end process for investigating: a crash, a memory bug, a race, a hang, a slow program. Five different playbooks, each under 60 seconds to describe.

Congratulations. You're a debugger.
