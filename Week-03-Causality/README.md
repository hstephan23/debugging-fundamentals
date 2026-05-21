# Week 3 - Causality Through State Changes

## Investigation

The program ends with suspicious state. The visible symptom is not the interesting moment. The interesting moment is when the state first changed.

This week trains causality: do not ask only where you noticed the bad value. Ask who wrote it.

## Mentor Opening

- Which value is suspicious?
- Where did you first observe it?
- Why might the observation point be later than the cause?
- What would prove who changed the value?
- What is fragile about watching `*ptr` instead of a stable variable?

## First Claim

Before using watchpoints, write:

```text
Claim:
Confidence:
State I need to watch:
Write that would support my claim:
Write that would weaken my claim:
```

## Evidence Round 1

Build and observe the program:

```bash
cd Week-03-Causality/example
make clean
make
./watchpoint_demo
gdb ./watchpoint_demo
```

Inside GDB:

```gdb
break main
run
watch secret
continue
continue
continue
```

At each stop, record:

- the old value
- the new value
- the source line
- the stack frame
- whether that write explains the final symptom

## Mentor Interruption

- Did the watchpoint stop where the value was noticed or where it changed?
- Which write is legitimate setup?
- Which write first violates your model?
- What does the stack say about who caused it?
- Are you watching the value, the pointer, or the memory currently pointed to?

## Evidence Round 2

If `rr` is installed, record and replay:

```bash
make rr
make replay
```

Inside replay:

```gdb
continue
watch secret
reverse-continue
bt
```

If `rr` is not installed, repeat the watchpoint pass and write what reverse execution would have let you test.

## Debrief

Watchpoints, debugger scripting, reverse execution, event logs, traces, and audit records are tools for finding causality through state changes. They are most useful when the symptom is far away from the cause.

The mature move is to stop reading source in order and instead ask the system where the state first changed.

## Apprentice Notes

Write one note:

```text
Suspicious state:
First claim:
Watchpoint:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- identify the watched state precisely
- distinguish the bad write from earlier legitimate writes
- name the stack frame that caused the state change
- explain what reverse execution would add
- describe a future invariant or assertion that would catch the state earlier

Weak answers:

- stop at the final bad value without finding the write
- say "watchpoint found it" without naming the write
- watch unstable pointer targets without noticing
- use reverse execution as a trick instead of a causality tool
