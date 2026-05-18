# Debugging Apprenticeship

A mentor-led curriculum for learning C debugging through investigations, discussion, evidence, and postmortems.

This is not a tool tour. Each week starts with a failure and asks the learner to make a claim, test it, interpret the evidence, and revise the model. GDB, core dumps, Valgrind, sanitizers, concurrency tools, logs, traces, and profiles are used as evidence generators.

## Who This Is For

Use this repo if:

- you already know enough C to read pointers, structs, allocation, and pthread examples
- you want to learn debugging as a repeatable discipline
- you have a mentor, study partner, or review group that can challenge your reasoning
- you are willing to write short investigation notes instead of only running commands

Solo learners can still use the repo. Read the mentor prompts out loud, answer them in your bug journal, and do not continue until you can name the evidence that changed your mind.

## How Sessions Work

Every module follows the same loop:

1. Restate the symptom.
2. Make a first claim.
3. Name what would weaken that claim.
4. Run the smallest useful experiment.
5. Separate direct evidence from interpretation.
6. Update the model.
7. Run a narrower experiment.
8. End with a prevention or postmortem note.

The learner should leave each session with a short note:

```text
Symptom:
First claim:
Experiment:
Evidence:
Model update:
Next move:
Prevention:
```

## Shared Guides

- [Mentor Guide](mentor-guide.md): how to run sessions, interrupt guesses, and demand evidence.
- [Learner Guide](learner-guide.md): how to prepare, answer, and keep a useful bug journal.
- [Investigation Template](investigation-template.md): the canonical structure for future modules.
- [Discussion Rubric](discussion-rubric.md): how to evaluate debugging reasoning.

## The Core Rule

Do not say a tool found the bug. Say what the tool showed.

Weak:

> Valgrind found a memory bug.

Strong:

> Valgrind reported an invalid write one byte past a heap allocation created in `make_buffer`, so the next experiment is to compare the allocation size with the write loop bound.

## The 10 Investigations

| Week | Module | Apprenticeship Focus |
|---|---|---|
| 1 | [Foundations](Week-01-Foundations/README.md) | Turn symptoms into testable hypotheses. |
| 2 | [GDB Fundamentals](Week-02-GDB-Fundamentals/README.md) | Choose useful breakpoints and inspect runtime state. |
| 3 | [Advanced GDB](Week-03-Advanced-GDB/README.md) | Trace causality through state changes. |
| 4 | [Core Dumps](Week-04-Core-Dumps/README.md) | Preserve and interpret postmortem evidence. |
| 5 | [Valgrind](Week-05-Valgrind/README.md) | Reconstruct ownership and lifetime from reports. |
| 6 | [Sanitizers](Week-06-Sanitizers/README.md) | Use precise runtime failures to narrow undefined behavior. |
| 7 | [Concurrency I](Week-07-Concurrency-1/README.md) | Separate nondeterminism from evidence. |
| 8 | [Concurrency II](Week-08-Concurrency-2/README.md) | Inspect blocked systems without making them worse. |
| 9 | [Logging and Observability](Week-09-Logging/README.md) | Debug through external signals instead of stopping the program. |
| 10 | [Capstone](Week-10-Capstone/README.md) | Run a full investigation and defend the postmortem. |

## Example Code Policy

Each `example/` directory is investigation material. Build it, run it, break on it, inspect it, and compare tool output against source.

The examples are intentionally small. That is the point: the learner should spend attention on the debugging loop, not on understanding a large codebase.

Compiled binaries are not curriculum source. They should be regenerated with `make` when needed.

## Mentor Expectations

The mentor should:

- ask for the learner's hypothesis before the command
- interrupt vague answers
- ask what would disprove the claim
- force one-variable experiments
- ask what the evidence showed directly
- end with prevention

The mentor should not:

- lecture through all concepts before the first observation
- accept "GDB found it" as an explanation
- let the learner keep changing code without naming evidence
- treat one passing concurrent run as proof

## Learner Expectations

The learner should:

- write short notes
- give confidence levels
- separate evidence from inference
- revise the model when evidence changes
- explain why the next experiment is smaller or sharper
- name how this bug could be easier to catch next time

## Tools Used

Most weeks assume a Linux environment or a Linux VM/container. Some tools have limited support on macOS.

Core tools:

- `gcc` or `clang`
- `make`
- `gdb`
- `valgrind`
- sanitizer-capable compiler
- pthreads
- `strace`
- `perf`
- `rr` where available

If a tool is unavailable, do not skip the discussion. Record what evidence that tool would have produced and choose the next best experiment.
