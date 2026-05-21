# Debugging Thinking Playbooks

These playbooks are short enough to read under pressure. Use the commands when they fit the stack in front of you; otherwise substitute the closest evidence source and keep the same reasoning shape.

---

## A process crashed

1. Keep the core dump and the binary with debug info together.
2. `gdb ./bin ./core` — or `coredumpctl gdb`.
3. `bt`, then `frame N` through the stack; `info args` + `info locals` at each.
4. Read the crash-site disassembly if symbols are thin (`disassemble $rip`).
5. Capture the chain of evidence in the bug journal before you start fixing.

Generic shape: preserve the failure artifact, inspect the state at failure time, separate crash site from root cause, and only then rerun or change code.

---

## A process hung

1. Don't kill it — capture it first.
2. `gdb -p <pid>`, then `thread apply all bt`.
3. Look for threads in `__lll_lock_wait` or `futex_wait` — those are blocked.
4. For each blocked thread: which lock is it waiting on, and who holds it?
5. If needed, `valgrind --tool=helgrind` on a reproducer later for confirmation.

Generic shape: preserve the live state, identify every actor that is waiting, name the resource or dependency each actor needs, and look for a cycle or missing wakeup.

---

## Memory is corrupting

1. First rebuild: `-fsanitize=address,undefined`. Run. Read the report.
2. If ASan is silent but you still suspect it, run under Valgrind memcheck.
3. Narrow the reproducer. Smaller inputs; fewer threads; deterministic seed.
4. In GDB, `watch` the suspicious variable and let the hardware watchpoint
   tell you who scribbled on it.
5. Fix the write, not the symptom.

Generic shape: identify the corrupted resource, find the first invalid write or ownership transfer, and fix the contract that allowed the bad state.

---

## Concurrency is suspicious

1. First rebuild: `-fsanitize=thread`. Run the test suite. Read reports.
2. For hangs, use the "process hung" playbook.
3. For wrong answers that go away in single-threaded mode, it's almost
   certainly a race. Re-run under `rr record --chaos` to perturb scheduling.
4. Check every shared variable: is it atomic, mutex-protected, or truly
   single-owner? If not, it's a race.

Generic shape: repeated wrong answers prove unreliability, not cause. Find the shared resource, conflicting operations, missing ordering rule, and the smallest reproducer.

---

## It's slow (performance as debugging)

1. Measure before you touch anything. `time`, then `perf stat`.
2. `perf record -g -- ./prog` and `perf report` to find the hotspot.
3. Flamegraph for a shareable picture.
4. Don't optimize the wrong function. Profile-driven only.
5. For cache / contention puzzles, `perf c2c` is invaluable.

Generic shape: define "slow," measure before changing anything, find where time is actually spent, and optimize only the proven bottleneck.

---

## Output is wrong

1. Capture the exact input, output, expected output, and environment.
2. Identify the first boundary where expected and actual state can be compared.
3. Check whether the bad state entered from input, transformation, persistence, cache, dependency, or rendering.
4. Move backward to the first disagreement, not forward from the final symptom.
5. Add a regression check at the boundary where the invariant first broke.

---

## An integration failed

1. Preserve request IDs, payload shape, status codes, retries, timestamps, and version/config diffs.
2. Decide which side owns the contract: caller, callee, transport, auth, schema, or environment.
3. Compare a known-good call with the failing call.
4. Inspect the first boundary where the two diverge.
5. Prevent recurrence with schema validation, contract tests, clearer errors, or compatibility checks.
