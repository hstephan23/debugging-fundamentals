# Week 2 - GDB Fundamentals

## Investigation

You have a small recursive Fibonacci program. Reading the source is allowed, but the apprenticeship focus is runtime state: where do you stop, what do you inspect, and how do you decide whether to step deeper or move back to the caller?

The mentor should keep the learner from wandering through lines. Every breakpoint must be a question.

## Mentor Opening

- What do you expect `fib(10)` to do?
- Where would runtime state first become informative?
- What question does your first breakpoint answer?
- What would make you inspect the caller instead of the current function?
- What would make stepping deeper a waste of time?

## First Claim

Before starting GDB, write:

```text
Claim:
Confidence:
First breakpoint:
Question this breakpoint answers:
Evidence that would change my mind:
```

## Evidence Round 1

Build and start the debugger:

```bash
cd Week-02-GDB-Fundamentals/example
make clean
make
gdb ./fib
```

Inside GDB:

```gdb
break fib
run 10
bt
info args
info locals
finish
```

Record the strongest observation from the stack, arguments, or locals. Do not write "GDB showed it." Write what GDB showed.

## Mentor Interruption

- What frame are you in?
- What are the current arguments?
- Which local value surprised you?
- Did `finish` confirm the function returned what you expected?
- Should the next move be `step`, `next`, `finish`, or `continue`? Why?

## Evidence Round 2

Use a narrower stop condition:

```gdb
delete breakpoints
break fib if n == 3
run 10
bt
info args
finish
```

Then try one instrumentation-style breakpoint:

```gdb
break fib
commands
silent
printf "fib called with n=%d\n", n
continue
end
run 5
```

## Debrief

A breakpoint is a question about state at a specific point in execution. Good GDB use is not stepping line by line until something feels wrong. It is stopping at boundaries, comparing expected state to actual state, and moving toward the first disagreement.

## Apprentice Notes

Write one note:

```text
Symptom or question:
First claim:
Breakpoint question:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- explain why the first breakpoint was chosen
- name a frame, argument, local, or return value
- justify stepping into, stepping over, finishing, or continuing
- use a conditional breakpoint to reduce noise
- describe how the next GDB session would be faster

Weak answers:

- list commands without explaining the questions they answered
- confuse caller and callee frames
- keep stepping after the relevant boundary was already tested
- treat the stack trace as the root cause instead of evidence
