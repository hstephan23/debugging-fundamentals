# Week 7 — Concurrency I: Data Races &amp; ThreadSanitizer

## Goal

Build a mental model of why concurrent C code is hard, and learn to find the most common class of concurrency bug — the data race — with ThreadSanitizer. Multi-threaded bugs are famously non-reproducible; the key skill is making them reproducible and observable.

## 30-minute pass

- **0–5 min:** Read the distinction between data race and race condition.
- **5–12 min:** `cd example && make`, then run `./race_counter` several times and observe the changing result.
- **12–21 min:** Run `make tsan`, then `./tsan_race`. Read the two access stacks in the report.
- **21–26 min:** Run `./race_counter_mutex` and `./race_counter_atomic` to confirm the fixed versions are stable.
- **26–30 min:** Journal the shared variable, the racing accesses, and which synchronization removed the race.

Deepen later: atomic memory orders, false sharing, and TSan limitations.

## Concepts to understand

- **A data race** is two threads accessing the same memory location concurrently, where at least one is a write, without synchronization. Per the C11 memory model, a data race is *undefined behavior* — the compiler is free to assume it never happens.
- **Data races are different from race conditions.** A race condition is a logical bug where the *outcome* depends on timing. A data race is a specific technical violation of the memory model. Every data race is a bug; not every race condition is a data race.
- **Memory ordering matters.** `x = 1; y = 2;` on thread A is not guaranteed to be seen in order by thread B unless there's a synchronization primitive in between. Modern CPUs and compilers both reorder. This is why mutexes and atomics exist.
- **Atomics (`stdatomic.h`) give you race-free shared access without locks.** `atomic_store`, `atomic_load`, and the memory-order parameters (`memory_order_relaxed`, `_acquire`, `_release`, `_seq_cst`) are the vocabulary.
- **ThreadSanitizer (TSan)** is a compiler-based race detector. It instruments every memory access and every synchronization primitive, maintains a happens-before graph, and reports when it finds two accesses that can race. Overhead is roughly 5–15×.

## Reading / watching

- "What Every Programmer Should Know About Memory" (Ulrich Drepper) — the concurrency-relevant chapters. Long but foundational.
- Hans Boehm's "How to miscompile programs with 'benign' data races" — why there's no such thing as a benign race.
- The TSan paper (Serebryany &amp; Iskhodzhanov, 2009) and the project's README.
- C11 `stdatomic.h` reference — cppreference has a clear overview.

## Core practice

### 1. Write a program that races, then find the race

```c
// race.c
#include <pthread.h>
#include <stdio.h>

static long counter = 0;

void *worker(void *arg) {
    for (int i = 0; i < 1000000; i++) counter++;
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&amp;t1, NULL, worker, NULL);
    pthread_create(&amp;t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%ld\n", counter);
}
```

Run it a few times without sanitizers — you'll see different final counts. Now build with TSan:

```
gcc -g -O1 -fsanitize=thread -fno-omit-frame-pointer -o race race.c -lpthread
./race
```

TSan prints a detailed race report: both stacks, both accesses, the memory location, and the fact that no synchronization mediates them. Fix it — first with a mutex, then with an atomic — and confirm TSan is silent.

### 2. Try more interesting races

Build a small pub/sub or producer/consumer with:

- A flag variable read by one thread, written by another
- A shared array, with one thread writing and one reading
- A struct where one field is protected by a mutex but a sibling field is not

Let TSan find each. Notice where it points you.

### 3. Learn the atomic memory orders

Write a tiny, contrived example for each of:

- `memory_order_relaxed` — counter that doesn't need ordering
- `memory_order_acquire` / `memory_order_release` — lock-free handoff
- `memory_order_seq_cst` — the default; slowest but strongest

Don't worry about "knowing when to use each" from memory — just *read* real code that uses them (kernel primitives, `jemalloc`, `liburcu`) and develop vocabulary.

### 4. False sharing &amp; `perf c2c`

Not strictly a correctness bug, but relevant: two threads writing to adjacent (but separate) variables in the same cache line produce false sharing — correct but 10× slower. Learn to pad structs with `alignas(64)` or equivalent. `perf c2c` visualizes this on Linux.

### 5. Tricky cases TSan can still struggle with

- Code that synchronizes via a condition variable TSan wasn't designed to understand (most work fine, edge cases don't).
- Code that uses raw inline assembly for synchronization.
- Signal handlers touching shared state.

For each, skim the TSan documentation on "limitations." You don't need to memorize — you just need to know TSan is not magical, and what to do when it's silent on something you're still worried about.

## Stretch

- Work through the first half of *C++ Concurrency in Action* (Anthony Williams). Yes, C++. The memory model and primitives are identical to C11, and the explanations are the clearest available.
- Read a well-known lock-free queue implementation (e.g., Dmitry Vyukov's bounded MPMC queue). Understand why each atomic operation has the order it has. This is hard — give it a full session.
- Explore `rr chaos mode` again: it deliberately stresses thread scheduling and is extraordinarily effective at triggering races.

## Checkpoint

You can move to Week 8 when you can:

- Explain the difference between a data race and a race condition.
- Write a minimal racy program, use TSan to find the race, and fix it with both a mutex and an atomic.
- Name and roughly explain the main `memory_order` values.
- Describe what false sharing is and how to detect/fix it.
