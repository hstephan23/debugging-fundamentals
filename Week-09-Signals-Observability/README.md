# Week 9 - Signals and Observability

## Investigation

You need evidence while the system keeps running. A debugger may be too disruptive, too late, or unavailable. Logs, traces, metrics, profiles, events, audit rows, and request histories become the way to ask questions from outside the failing path.

This week is about choosing the least disruptive signal that can answer the current question.

## Mentor Opening

- What can you learn without stopping the program?
- What question should a log line answer?
- What question should a syscall trace answer?
- What question should a profile answer?
- When is adding instrumentation better than attaching a tool?

## First Claim

Before running the server, write:

```text
Claim:
Confidence:
External signal I expect to help:
Question that signal answers:
Evidence that would weaken this:
```

## Evidence Round 1

Build and inspect structured logs:

```bash
cd Week-09-Signals-Observability/example
make clean
make
LOG_LEVEL=debug ./server
```

Stop it after you have enough output. Record:

- one complete log line
- timestamp or ordering clue
- level
- source or event field
- key-value pair that answers a debugging question

## Mentor Interruption

- What did you learn without a debugger?
- Which log field carried the most signal?
- Which line was noise?
- What would you add if this failed in production?
- Is this a source-level question, an OS-boundary question, or a performance question?

## Evidence Round 2

Use the least disruptive matching tool.

For OS-boundary evidence, run the server in one terminal:

```bash
./server
```

Then attach from another terminal if `strace` is available:

```bash
strace -f -tt -e openat,read,write -p $(pgrep server)
```

For CPU evidence:

```bash
./cpu_hog
perf record -g ./cpu_hog
perf report
```

If `strace` or `perf` is unavailable, compare `LOG_LEVEL=info` and `LOG_LEVEL=debug`, then write what the missing tool would have answered.

## Debrief

Observability is debugging without stopping the world. Good logs, traces, metrics, and events are not narration. They are structured answers to future questions.

The right signal depends on the boundary: program state, service interaction, operating-system interaction, persistence, external dependency, or time spent.

## Apprentice Notes

Write one note:

```text
Question:
First claim:
Signal chosen:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- choose a signal based on the question
- quote a specific log, syscall, or profile observation
- distinguish useful fields from noise
- explain when not to attach a debugger
- propose a better future log, trace point, metric, event, or measurement

Weak answers:

- add free-form prints with no question
- collect logs without reading them
- profile before defining "slow"
- treat observability as monitoring rather than investigation
