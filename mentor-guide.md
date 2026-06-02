# Mentor Guide

This curriculum is a debugging apprenticeship. Your job is not to explain diagnostics up front. Your job is to keep the learner moving from symptom to hypothesis to evidence to prevention.

## Session Rhythm

Use this loop in every session:

1. Ask the learner to restate the symptom.
2. Ask for the first hypothesis and confidence level.
3. Ask what observation would weaken that hypothesis.
4. Pick the smallest question that can identify useful evidence.
5. Discuss the evidence source.
6. Separate direct evidence from interpretation.
7. Ask for the updated model and the next question.
8. End with a short investigation note.

The goal is not a perfect first guess. The goal is controlled model updates.

## When To Interrupt

Interrupt when the learner:

- names a root cause without evidence
- says a diagnostic source "showed the bug" without naming the exact signal
- changes several variables at once
- keeps speculating after a sharper evidence question is available
- trusts one passing run of concurrent code
- treats a debugger, log, trace, test, profile, runtime report, or static warning as the root cause instead of evidence
- skips the prevention question after finding the failure

Use short questions:

- What did that prove?
- What are you inferring?
- What are you still assuming?
- What would make this theory false?
- What is the next smallest question?

## Evidence Standard

A strong learner answer names:

- the question being asked
- the observed or expected output, line, value, frame, report, log entry, timing, artifact, or user-visible fact
- the hypothesis it changed
- the next question or prevention step

## Handling Wrong Hypotheses

Wrong hypotheses are useful if they are tested cleanly. Do not let the learner hide a wrong guess. Make them write:

- what they believed
- why it was plausible
- what evidence weakened it
- what model replaced it

After three rounds that do not change the model, stop. Restart from the symptom and list known facts separately from assumptions.

## Ending A Session

Do not end on "fixed" or "understood" alone. End with an investigation note:

```text
Symptom:
First claim:
Question or evidence source:
Evidence:
Model update:
Next move:
Prevention:
```

If the bug is solved, the next move can be a prevention change, test, assertion, log line, or playbook update.
