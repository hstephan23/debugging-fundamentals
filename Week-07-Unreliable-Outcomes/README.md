# Week 7 - Unreliable Outcomes

## Discussion Goal

Practice reasoning about failures that do not appear the same way every time.

## Opening Prompts

- What changed between attempts?
- What stayed the same?
- What shared state, shared resource, schedule, cache, clock, queue, dependency, retry, or environment input might affect the outcome?
- Why is one passing attempt weak evidence?
- What would count as stronger evidence than "it failed once" or "it passed once"?

## First Claim Prompts

- What source of nondeterminism do you suspect first?
- How confident are you?
- What observation would support that source?
- What observation would weaken it?
- What hidden input might you be ignoring?

## Repetition Prompts

- What can repeated attempts prove?
- What can repeated attempts never prove by themselves?
- How many outcomes have you observed?
- Are the differences random, patterned, clustered, time-based, load-based, input-based, or environment-based?
- What would make the symptom more reproducible without changing the bug?

## Ordering Prompts

- Which operations must happen in a particular order for the system to be correct?
- Which operations are allowed to happen concurrently?
- Which actor owns the shared state at each moment?
- Where is the ownership or ordering rule enforced?
- What would prove the rule is missing rather than merely slow?

## Mentor Interruption Prompts

- Are you treating probability as proof?
- Did the latest run change your model or only your mood?
- What evidence identifies the conflicting actors?
- What stronger signal would connect the symptom to a specific ordering failure?
- What would make a timing fix look successful while leaving the bug intact?

## Model Update Prompts

- What pattern emerged across attempts?
- Which hidden input became more suspicious?
- Which explanation became less plausible?
- What narrower condition should the next investigation control?
- What is the smallest change to the question that would reduce uncertainty?

## Prevention Prompts

- What ownership, ordering, idempotency, retry, timeout, synchronization, or isolation rule is missing?
- What should become deterministic?
- What should be measured across attempts?
- What future signal would identify the conflicting actors faster?
- What proof would be strong enough to trust a fix?

## Apprentice Note Prompts

- Symptom:
- Variable outcomes:
- Suspected hidden input:
- First claim:
- Evidence across attempts:
- Ordering or ownership question:
- Model update:
- Prevention:
