# Mentor Guide

This curriculum is a debugging apprenticeship. Your job is not to explain every tool up front. Your job is to keep the learner moving from symptom to hypothesis to experiment to evidence.

## Session Rhythm

Use this loop in every session:

1. Ask the learner to restate the symptom.
2. Ask for the first hypothesis and confidence level.
3. Ask what observation would weaken that hypothesis.
4. Pick the smallest experiment that can produce evidence.
5. Run the experiment.
6. Separate direct evidence from interpretation.
7. Ask for the updated model and the next experiment.
8. End with a short investigation note.

The goal is not a perfect first guess. The goal is controlled model updates.

## When To Interrupt

Interrupt when the learner:

- names a root cause without evidence
- says a tool "showed the bug" without naming the exact signal
- changes several variables at once
- keeps reading source after a runtime observation would be cheaper
- trusts one passing run of concurrent code
- treats a sanitizer, Valgrind, or GDB report as the root cause instead of evidence
- skips the prevention question after finding the failure

Use short questions:

- What did that prove?
- What are you inferring?
- What are you still assuming?
- What would make this theory false?
- What is the next smallest experiment?

## Evidence Standard

A strong learner answer names:

- the command or action
- the observed output, line, value, frame, report, log entry, or timing
- the hypothesis it changed
- the next experiment or prevention step

Weak answer:

> GDB showed it was in `fib`.

Strong answer:

> I expected recursion depth to be the problem. Stopping in `fib` showed `n` was already wrong at the function boundary, so recursion is probably not the first cause. The next experiment is to inspect the caller.

## Handling Wrong Hypotheses

Wrong hypotheses are useful if they are tested cleanly. Do not let the learner hide a wrong guess. Make them write:

- what they believed
- why it was plausible
- what evidence weakened it
- what model replaced it

After three experiments that do not change the model, stop. Restart from the symptom and list known facts separately from assumptions.

## Ending A Session

Do not end on "fixed" or "understood" alone. End with an investigation note:

```text
Symptom:
First claim:
Experiment:
Evidence:
Model update:
Next move:
Prevention:
```

If the bug is solved, the next move can be a prevention change, test, assertion, log line, or playbook update.
