# Debugging Playbooks

Five situations, five playbooks. Short enough to read in 30 seconds when the
pressure's on.

---

## A process crashed

1. Keep the core dump and the binary with debug info together.
2. `gdb ./bin ./core` — or `coredumpctl gdb`.
3. `bt`, then `frame N` through the stack; `info args` + `info locals` at each.
4. Read the crash-site disassembly if symbols are thin (`disassemble $rip`).
5. Capture the chain of evidence in the bug journal before you start fixing.

---

## A process hung

1. Don't kill it — capture it first.
2. `gdb -p <pid>`, then `thread apply all bt`.
3. Look for threads in `__lll_lock_wait` or `futex_wait` — those are blocked.
4. For each blocked thread: which lock is it waiting on, and who holds it?
5. If needed, `valgrind --tool=helgrind` on a reproducer later for confirmation.

---

## Memory is corrupting

1. First rebuild: `-fsanitize=address,undefined`. Run. Read the report.
2. If ASan is silent but you still suspect it, run under Valgrind memcheck.
3. Narrow the reproducer. Smaller inputs; fewer threads; deterministic seed.
4. In GDB, `watch` the suspicious variable and let the hardware watchpoint
   tell you who scribbled on it.
5. Fix the write, not the symptom.

---

## Concurrency is suspicious

1. First rebuild: `-fsanitize=thread`. Run the test suite. Read reports.
2. For hangs, use the "process hung" playbook.
3. For wrong answers that go away in single-threaded mode, it's almost
   certainly a race. Re-run under `rr record --chaos` to perturb scheduling.
4. Check every shared variable: is it atomic, mutex-protected, or truly
   single-owner? If not, it's a race.

---

## It's slow (performance as debugging)

1. Measure before you touch anything. `time`, then `perf stat`.
2. `perf record -g -- ./prog` and `perf report` to find the hotspot.
3. Flamegraph for a shareable picture.
4. Don't optimize the wrong function. Profile-driven only.
5. For cache / contention puzzles, `perf c2c` is invaluable.
