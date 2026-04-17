# Week 8 — Concurrency II: Deadlocks &amp; Live Thread Debugging

## Goal

Handle the second big class of concurrency bugs — deadlocks, livelocks, and priority-inversion-style hangs — and learn to inspect a live multi-threaded program in GDB. A hung process is a very different investigation from a crash, and it wants a different toolkit.

## Concepts to understand

- **Deadlock requires four conditions** (Coffman's conditions): mutual exclusion, hold &amp; wait, no preemption, circular wait. Break any one of the four and deadlock becomes impossible.
- **Lock hierarchies** are the classic prevention: all threads acquire locks in a consistent global order, which makes circular waits impossible. Documented once, enforced everywhere.
- **Helgrind** (a Valgrind tool) detects potential deadlocks by tracking lock acquisition order and reporting cycles. It also reports data races, though TSan is usually more precise.
- **`pthread_mutex_t` has variants.** Normal, errorcheck (detects self-deadlock), recursive. Know when each is appropriate. Default `PTHREAD_MUTEX_NORMAL` gives undefined behavior on double-lock by the same thread — a common bug source.
- **Live thread debugging in GDB** is a distinct skill. `info threads`, `thread N`, `thread apply all bt` — the last one is the single most valuable command for diagnosing a hang.
- **Livelock** — threads are running but making no progress, each reacting to another's reaction. Rarer than deadlock, subtler, and usually a design flaw rather than a lock-ordering bug.

## Reading / watching

- Helgrind manual.
- "Deadlocks: what they are, how to find them, how to avoid them" — plenty of versions; any textbook-style one works.
- The POSIX threads man pages for `pthread_mutex_*` — read them in full at least once.

## Core practice

### 1. Build a classic two-lock deadlock

```c
static pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *_) {
    pthread_mutex_lock(&amp;a);
    usleep(1000);
    pthread_mutex_lock(&amp;b);
    // ... use both
    pthread_mutex_unlock(&amp;b);
    pthread_mutex_unlock(&amp;a);
    return NULL;
}

void *t2(void *_) {
    pthread_mutex_lock(&amp;b);
    usleep(1000);
    pthread_mutex_lock(&amp;a);
    // ... use both
    pthread_mutex_unlock(&amp;a);
    pthread_mutex_unlock(&amp;b);
    return NULL;
}
```

Run it. Confirm it hangs. Now:

- **GDB approach:** attach with `gdb -p`, then `thread apply all bt`. Each thread is blocked in `__lll_lock_wait` or similar. Look at the frame above it — you see exactly which mutex each thread holds and which it's trying to acquire.
- **Helgrind approach:** run under `valgrind --tool=helgrind ./prog`. It reports the lock-order violation directly.

Fix by establishing a consistent lock order (always A then B). Confirm Helgrind is happy and the hang goes away.

### 2. `errorcheck` and `recursive` mutexes

Write code that locks the same mutex twice on the same thread — classic bug in a refactor. Run it with default, errorcheck, and recursive mutex types. Observe the different behaviors:

- Default: undefined behavior (often hang on Linux).
- Errorcheck: `pthread_mutex_lock` returns `EDEADLK`. Assertable.
- Recursive: counter increments; don't use casually — it often hides design bugs.

### 3. Condition variables &amp; the spurious-wakeup rule

Write a producer/consumer using `pthread_cond_wait`. Deliberately use `if` instead of `while` around the condition check:

```c
pthread_mutex_lock(&amp;m);
if (queue_empty(&amp;q))         // BUG — should be while
    pthread_cond_wait(&amp;cv, &amp;m);
// ... pop
pthread_mutex_unlock(&amp;m);
```

Then add artificial spurious wakeups (send extra `pthread_cond_signal`s from a third thread) and watch it break. Fix by replacing `if` with `while` and internalize why: `pthread_cond_wait` can return spuriously, and even non-spurious wakeups can race. The invariant is always *re-check the predicate*.

### 4. Debugging a hang in production style

This is the key exercise of the week. Imagine a real-world scenario:

- A server process hangs. You can't restart it yet — you need to know why first.
- You have `gdb`, the binary with `-g`, and no reproducer.

Practice:

```
gdb -p $(pgrep myserver)
(gdb) info threads
(gdb) thread apply all bt
(gdb) thread apply all bt full     # with locals
```

Save the output to a file (`set logging on`) so you can study it offline. Look for threads in `__lll_lock_wait` — they're the ones blocked. Then for each, walk up the stack to find which lock, acquired by whom.

If you have `pstack` installed, `pstack $(pgrep myserver)` is a quick way to get all thread backtraces without starting GDB.

### 5. Design practices that prevent this whole category

Write these down in your notes:

- Document a global lock order for your codebase, even informally.
- Prefer *finer* locking (per-object) over *coarser*, but not so fine that you need many locks at once.
- Consider lock-free designs (`stdatomic.h` queues, RCU) where contention matters.
- Use RAII-like patterns in C via `pthread_cleanup_push` / `pop`, or write `__attribute__((cleanup))` helpers, so locks are released on every path.
- Have timeouts on lock acquisitions in long-lived daemons if it's critical that they can't hang forever.

## Stretch

- Read the `liburcu` (userspace RCU) documentation. RCU is a deep, beautiful alternative to locks for read-heavy workloads.
- Try `drd`, Valgrind's other thread checker. It overlaps Helgrind but finds a slightly different set.
- Explore kernel `lockdep` writeups to see how the Linux kernel's lock dependency checker works — the same ideas apply to userspace design.

## Checkpoint

You can move to Week 9 when you can:

- Define Coffman's four deadlock conditions and name the standard prevention for each.
- Produce and debug a two-lock deadlock using `thread apply all bt`.
- Explain why `pthread_cond_wait` must be called in a `while` loop, not an `if`.
- Describe your strategy for diagnosing a hung process you can't kill yet.
