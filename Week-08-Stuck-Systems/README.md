# Week 8 - Stuck Systems

## Discussion Goal

Practice investigating a system that appears stuck while its live state is still the best evidence.

## Opening Prompts

- How do you know the system is hung rather than slow?
- What evidence can you gather without disturbing it?
- What would be destroyed by killing, restarting, retrying, or redeploying?
- Which actors might be waiting?
- What resources, dependencies, queues, locks, permits, workers, or external calls might they be waiting on?

## First Claim Prompts

- What kind of wait do you suspect?
- How confident are you?
- Which actor do you expect to be blocked?
- What do you expect it to be waiting for?
- What evidence would show this is not a deadlock, starvation, missing wakeup, dependency wait, or slow operation?

## Live-State Prompts

- What can the system tell you while it is still stuck?
- Which actors must be inspected together?
- Which actor is waiting?
- Which actor might hold or control the thing being waited on?
- Is there a cycle, a missing signal, a saturated pool, a stuck dependency, or a long-running operation?

## Mentor Interruption Prompts

- Are you about to destroy the best evidence?
- Are you inspecting every actor or only the one that looks frozen?
- What does "waiting" mean in this system?
- What resource is scarce or exclusive?
- What would prove this is slowness rather than stuckness?

## Model Update Prompts

- What wait relationship can you defend from evidence?
- What wait relationship are you inferring?
- What actor or dependency remains uninspected?
- What narrower question should the next evidence source answer?
- What would make a longer timeout hide the bug instead of fixing it?

## Prevention Prompts

- What ordering, timeout, cancellation, retry, backpressure, lock discipline, queue visibility, or dependency health rule is missing?
- What should be observable before someone reaches for a restart?
- What should the system report when an actor waits too long?
- What stuck state should be impossible?
- What operational runbook question would shorten the next incident?

## Apprentice Note Prompts

- Symptom:
- Hung or slow:
- Preserved live evidence:
- Suspected wait:
- Evidence:
- Updated model:
- Next question:
- Prevention:
