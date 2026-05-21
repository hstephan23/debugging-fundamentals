# Week 8 - Nondeterminism II

## Investigation

A program appears hung. The wrong first move is to kill it and start guessing. The right first move is to inspect the live process while it is still preserving the evidence.

This week is about blocked systems, worker state, lock order, queue waits, dependency waits, and live debugging discipline.

## Mentor Opening

- How do you know the program is hung rather than slow?
- What evidence can you gather without changing the process?
- Which threads need stack traces?
- What lock-order story would explain a deadlock?
- What would killing the process destroy?

## First Claim

Before attaching tools, write:

```text
Claim:
Confidence:
Thread state I expect:
Lock or wait I suspect:
Evidence that would weaken this:
```

## Evidence Round 1

Build and run the deadlock example:

```bash
cd Week-08-Nondeterminism-2/example
make clean
make
./deadlock
```

Let it hang briefly. In another terminal, inspect it:

```bash
gdb -p $(pgrep deadlock)
```

Inside GDB:

```gdb
thread apply all bt
detach
quit
```

Record which threads are blocked and where.

## Mentor Interruption

- Which thread is waiting?
- What is it waiting on?
- Which other thread might hold what it needs?
- Does each thread hold one lock while waiting for another?
- What evidence would show this is not a deadlock?

## Evidence Round 2

Compare with tool-assisted and fixed runs:

```bash
make helgrind
./deadlock_fixed
./errorcheck_mutex
./cond_spurious
```

If Valgrind is unavailable, record that and compare the fixed program plus the live GDB thread evidence.

## Debrief

Live debugging is evidence preservation. A hung process, stuck job, blocked worker, or frozen request is a preserved state: inspect stacks, waits, queues, dependencies, and lock order before disturbing it.

The mature fix is an ownership, ordering, retry, timeout, or synchronization design, not simply a longer timeout.

## Apprentice Notes

Write one note:

```text
Symptom:
First claim:
Live evidence:
Blocked thread:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- distinguish hang from slowness
- capture all thread backtraces
- identify a plausible wait cycle
- compare live evidence with Helgrind or fixed behavior
- propose a lock-order or synchronization prevention rule

Weak answers:

- kill the process before inspecting it
- rely on timeout length as proof
- inspect only one thread
- call every blocked syscall a deadlock
