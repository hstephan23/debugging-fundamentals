# Debugging Thinking Apprenticeship

A mentor-led curriculum for learning how to approach software failures through investigation, critical thinking, evidence, and postmortems.

This is not a tour of C, GDB, or any single toolchain. Each week starts with a failure and asks the learner to make a claim, test it, interpret the evidence, and revise the model. The included examples use small systems programs because they make failure visible, but the real subject is the debugging loop you can use in any stack.

## Who This Is For

Use this repo if:

- you want to learn debugging as a repeatable thinking discipline
- you have a mentor, study partner, or review group that can challenge your reasoning
- you are willing to write short investigation notes instead of only running commands
- you can tolerate examples in one implementation language while practicing ideas that transfer to many

Solo learners can still use the repo. Read the mentor prompts out loud, answer them in your bug journal, and do not continue until you can name the evidence that changed your mind.

## What You Are Practicing

The curriculum is built around habits that transfer across languages, frameworks, and runtimes:

- turn vague symptoms into specific, observable questions
- separate what happened from why you think it happened
- make hypotheses that can be weakened, not just confirmed
- choose the smallest experiment that can reduce uncertainty
- preserve evidence before changing the system
- compare alternative explanations instead of chasing the first plausible story
- end with a prevention move: test, assertion, invariant, log, type, monitor, review rule, or design change

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

Do not say a tool found the bug. Say what evidence changed your model.

Weak:

> The debugger showed the bug.

Strong:

> The request had a valid ID at the API boundary, but the stored row had a null owner before authorization ran, so the next experiment is to inspect the persistence path that creates or updates that row.

## The 10 Investigations

| Week | Module | Apprenticeship Focus |
|---|---|---|
| 1 | [Foundations](Week-01-Symptoms-Inputs-Claims/README.md) | Turn symptoms into testable hypotheses. |
| 2 | [Runtime State](Week-02-Runtime-State/README.md) | Stop at useful boundaries and inspect live state. |
| 3 | [Causality](Week-03-Causality/README.md) | Trace where state first changed, not only where it was noticed. |
| 4 | [Postmortem Evidence](Week-04-Postmortem-Evidence/README.md) | Preserve and interpret evidence after a failure. |
| 5 | [Ownership and Lifetime](Week-05-Ownership-Lifetime/README.md) | Reconstruct responsibility from reports and traces. |
| 6 | [Runtime Checks](Week-06-Runtime-Checks/README.md) | Use precise failures to narrow violated boundaries. |
| 7 | [Nondeterminism I](Week-07-Nondeterminism-1/README.md) | Separate unreliable outcomes from stronger evidence. |
| 8 | [Nondeterminism II](Week-08-Nondeterminism-2/README.md) | Inspect blocked systems without making them worse. |
| 9 | [Signals and Observability](Week-09-Signals-Observability/README.md) | Debug through external signals instead of stopping the system. |
| 10 | [Full Investigation](Week-10-Full-Investigation/README.md) | Run a full investigation and defend the postmortem. |

## Example Code Policy

Each `example/` directory is investigation material. Build it, run it, break on it, inspect it, and compare tool output against source.

The examples are intentionally small and mostly written in C. That is a fixture choice, not the learning objective. The learner should spend attention on symptom framing, uncertainty reduction, evidence quality, and prevention rather than on memorizing language trivia.

Compiled binaries are not curriculum source. They should be regenerated with the local build command when needed.

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
- accept "the tool found it" as an explanation
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

Most examples assume a Linux environment or a Linux VM/container. Some tools have limited support on macOS.

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

For another stack, substitute equivalent evidence sources:

- browser devtools, server logs, traces, metrics, database query logs
- failing tests, property checks, type errors, lint output
- request IDs, queue events, job histories, deployment diffs
- debugger breakpoints, profiles, heap snapshots, crash reports
