# Week 9 - Choose Useful Signals

## Discussion Goal

Practice choosing the least disruptive signal that can answer the current debugging question.

## Opening Prompts

- What do you need to learn while the system keeps running?
- What would be too disruptive to stop, attach to, restart, or modify?
- What signal already exists?
- What signal is missing?
- What question should each signal answer?

## Signal Selection Prompts

- Is this a program-state question, dependency question, persistence question, user-flow question, timing question, resource question, or deployment question?
- Would a log, trace, metric, profile, audit event, request history, database observation, browser artifact, or user-visible artifact answer it best?
- Which signal is closest to the boundary where the failure appears?
- Which signal is cheapest to collect?
- Which signal has the highest risk of misleading you?

## First Claim Prompts

- What do you expect the signal to show?
- How confident are you?
- What field, dimension, event, span, metric, or timestamp should matter?
- What would make the signal noisy?
- What would weaken your claim?

## Evidence Interpretation Prompts

- What did the signal show directly?
- What did it not show?
- Which field carried the most information?
- Which field was only decoration?
- Which missing field would have shortened the investigation?

## Mentor Interruption Prompts

- Are you collecting signals because they answer a question or because they are available?
- What boundary does this signal observe?
- What would a different signal see that this one cannot?
- Are you reading the signal or only gathering it?
- What would you add only after proving the existing signals are insufficient?

## Model Update Prompts

- Which theory did the signal support?
- Which theory did it weaken?
- Which boundary should be inspected next?
- What would a higher-cardinality or lower-level signal reveal?
- What evidence would justify adding new instrumentation?

## Prevention Prompts

- What should the system emit next time?
- What field, metric, trace edge, event, correlation ID, or audit row is missing?
- What should be sampled, retained, alerted, or summarized?
- What signal would help during an incident without exposing sensitive data?
- How do you keep observability from becoming noisy narration?

## Apprentice Note Prompts

- Question:
- Signal chosen:
- Why this signal:
- Evidence:
- Missing signal:
- Model update:
- Next question:
- Prevention:
