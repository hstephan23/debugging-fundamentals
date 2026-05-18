# Week 4 - Core Dumps

## Investigation

A program crashed outside your interactive debugger session. You do not get to rerun casually and hope the same thing happens. Your first job is to preserve postmortem evidence and inspect the state the process left behind.

This week is about debugging after the fact.

## Mentor Opening

- What evidence exists after a process crashes?
- What would you destroy by immediately changing code or rerunning with different input?
- What do you need from the binary to make the crash readable?
- What stack frame is likely to be the symptom rather than the cause?
- What would make a core dump more useful than a live rerun?

## First Claim

Before enabling or inspecting core dumps, write:

```text
Claim:
Confidence:
Evidence I expect in the core:
Frame I expect to inspect first:
Evidence that would weaken this:
```

## Evidence Round 1

Build and reproduce the crash:

```bash
cd Week-04-Core-Dumps/example
make clean
make
ulimit -c unlimited
./crash "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
```

Record:

- the exact input
- whether a core file appeared locally
- whether your system stores cores through `coredumpctl`
- the crash signal or terminal message

## Mentor Interruption

- What did you preserve before changing anything?
- Is the crash input part of the evidence?
- Are debug symbols available?
- What would be different if this happened on a production machine?
- Which fact would you lose if you cleaned the directory now?

## Evidence Round 2

Inspect the postmortem state. Use the command that fits your system:

```bash
gdb ./crash ./core
```

or:

```bash
coredumpctl gdb crash
```

Inside GDB:

```gdb
bt
frame 2
info args
info locals
```

If no core is available, write the operating-system reason and inspect what evidence you would need: binary path, input, crash signal, debug symbols, and core-storage policy.

## Debrief

Core dumps are evidence snapshots. They let you ask what the process knew at the crash, not what a later rerun happens to show. The mature debugging move is to preserve the artifact, verify symbols, inspect the stack, and only then decide what to rerun.

## Apprentice Notes

Write one note:

```text
Symptom:
Crash artifact:
First claim:
Experiment:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- preserve the crashing input and artifact
- name whether the core came from a file or `coredumpctl`
- distinguish crashing frame from root-cause frame
- inspect args and locals before changing code
- identify what production crash reports should capture

Weak answers:

- rerun repeatedly without preserving the first crash
- inspect only the top frame
- ignore missing symbols
- treat lack of local `core` file as lack of postmortem evidence
