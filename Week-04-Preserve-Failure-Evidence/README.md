# Week 4 - Preserve Failure Evidence

## Discussion Goal

Use a failure that already happened to practice preserving evidence before changing the system.

## Opening Prompts

- What failed, and how do you know it failed?
- What evidence exists right now that might disappear if you restart, retry, clean up, deploy, or edit?
- What artifact, input, timestamp, request ID, screenshot, log line, trace, dump, or report should be preserved first?
- What evidence would be hardest to recreate later?
- What part of the current state is evidence, and what part is interpretation?

## First Claim Prompts

- What is your first explanation for the failure?
- How confident are you?
- What preserved artifact would support that explanation?
- What preserved artifact would weaken it?
- What are you tempted to change before you have earned the right to change it?

## Evidence Quality Prompts

- Which artifact is closest to the moment of failure?
- Which artifact only shows the aftermath?
- Which facts are missing from the failure report?
- What context would make the artifact readable to someone else?
- What would a future responder need in order to continue the investigation without you?

## Mentor Interruption Prompts

- What have you preserved before touching the system?
- What would be destroyed by a casual rerun?
- Are you treating the first visible failure point as the cause?
- What are you assuming about the environment?
- What evidence would distinguish "this is where it crashed" from "this is why it crashed"?

## Model Update Prompts

- What did the preserved evidence show directly?
- What did it fail to show?
- Which part of your first claim became stronger?
- Which part became weaker?
- What narrower question should the next evidence source answer?

## Prevention Prompts

- What should the system capture automatically next time?
- What field, trace, dump, event, or report was missing?
- What retention rule would protect useful evidence?
- What cleanup or retry behavior might be hiding failures?
- What would make this class of failure easier to investigate under pressure?

## Apprentice Note Prompts

- Symptom:
- Preserved evidence:
- First claim:
- Evidence that supported it:
- Evidence that weakened it:
- Updated model:
- Next question:
- Prevention:
