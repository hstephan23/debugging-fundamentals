# Week 5 - Reconstruct Responsibility

## Discussion Goal

Practice reconstructing responsibility: who created a thing, who owned it, who changed it, who should have cleaned it up, and who used it after the contract was broken.

## Opening Prompts

- What resource, value, object, record, session, handle, job, or transaction appears to have the wrong lifetime?
- Who creates it?
- Who is allowed to mutate it?
- Who is responsible for releasing, closing, committing, expiring, or invalidating it?
- Who observed it after the contract had already been broken?

## Contract Prompts

- What is the ownership rule supposed to be?
- Is ownership exclusive, shared, transferred, borrowed, cached, leased, or implicit?
- Where is that rule written down?
- Where is that rule only assumed?
- What would make the rule impossible for a future maintainer to miss?

## First Claim Prompts

- What responsibility boundary do you think failed?
- How confident are you?
- What evidence would connect the symptom to the creator?
- What evidence would connect the symptom to the last valid owner?
- What evidence would prove the failing user is only the messenger?

## Evidence Quality Prompts

- Does the evidence identify the bad use, the bad creation, the bad transfer, the missing cleanup, or only the final symptom?
- What timeline can you reconstruct from the evidence?
- Which actor had enough information to prevent the failure?
- Which actor merely inherited broken state?
- What missing event would complete the responsibility story?

## Mentor Interruption Prompts

- Are you explaining the contract or only naming the symptom?
- What changed ownership?
- What should have happened when ownership changed?
- What assumption did the caller and callee make about each other?
- What would make the same failure happen in a different stack or runtime?

## Model Update Prompts

- What responsibility story did the evidence support?
- Where is the first contract break you can defend?
- What competing responsibility story remains plausible?
- What question would separate those stories?
- What is the smallest follow-up investigation that would reduce that uncertainty?

## Prevention Prompts

- What invariant should be explicit?
- What cleanup path is missing or too easy to skip?
- What naming, type, review rule, lifecycle event, guard, or ownership boundary would make the contract visible?
- What should fail earlier?
- What should be impossible to express?

## Apprentice Note Prompts

- Symptom:
- Resource or state involved:
- Expected ownership rule:
- First claim:
- Evidence:
- Contract break:
- Remaining uncertainty:
- Prevention:
