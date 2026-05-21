# Investigation Template

Use this template when adding or rewriting a module.

````md
# Week N - Theme

## Investigation

Describe the symptom, the system under investigation, and the constraint. Keep this short. The learner should want to inspect evidence, not read a lecture.

## Mentor Opening

- What failed, and how do you know?
- What is your first hypothesis?
- What would make that hypothesis weaker?
- What is the smallest experiment that could produce useful evidence?

## First Claim

Before running a tool, write:

- claim:
- confidence:
- evidence that would support it:
- evidence that would weaken it:

## Evidence Round 1

Run the first experiment. Use the local command that produces the strongest evidence for this system.

```bash
# command goes here
```

Record the exact command and the strongest observation.

## Mentor Interruption

- What did the tool show directly?
- What are you inferring from that output?
- Which assumption changed?
- What are you still unable to prove?

## Evidence Round 2

Run a narrower experiment based on the model update.

```bash
# command goes here
```

Record whether the result supports, weakens, or redirects the current hypothesis.

## Debrief

Summarize:

- root cause or current best theory
- false lead avoided
- strongest signal
- prevention step

## Apprentice Notes

Write a short investigation note:

```text
Symptom:
First claim:
Experiment:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- name the exact evidence
- separate observation from interpretation
- update the model after each experiment
- choose the next experiment from the evidence
- include a prevention step

Weak answers:

- name only the tool
- explain before observing
- change multiple variables at once
- stop after finding a line without explaining why it failed
````
