# Week 10 - Defend The Investigation

## Discussion Goal

Run a complete debugging conversation from symptom to defended conclusion.

## Opening Prompts

- What kind of failure is this?
- What makes that classification plausible?
- What evidence must be preserved before changing anything?
- What would make your first theory false?
- What prevention step would make this easier next time?

## Investigation Framing Prompts

- Is this primarily a crash, hang, invalid state, data loss, nondeterminism, failed integration, incorrect output, slowness, or something else?
- What is the user-visible symptom?
- What system boundary first noticed the problem?
- What system boundary might have created the problem?
- What evidence source is closest to the failure?

## First Claim Prompts

- What is your first claim?
- How confident are you?
- What evidence would support it?
- What evidence would weaken it?
- What false lead are you most likely to chase?

## Evidence Round Prompts

- What evidence did you preserve?
- Why did you choose that evidence source first?
- What did it show directly?
- What are you inferring?
- What remains unproven?

## Narrowing Prompts

- What uncertainty remains after the first evidence round?
- What is the smallest follow-up question?
- What evidence would separate the top two theories?
- What result would redirect the investigation?
- What result would justify stopping investigation and moving to prevention?

## Postmortem Prompts

- What failed?
- Who or what noticed it?
- What evidence was preserved?
- What path did the investigation take?
- What was the strongest evidence?
- What conclusion is proportional to the evidence?
- What false lead was avoided?
- What prevention step follows from the actual evidence?

## Mentor Challenge Prompts

- Which sentence in the postmortem is unsupported?
- Where did you confuse observation with interpretation?
- Where did confidence move too far ahead of evidence?
- What would an experienced skeptic challenge first?
- What should be rewritten to be more precise?

## Apprentice Note Prompts

- Failure class:
- First claim:
- Evidence round 1:
- Model update:
- Evidence round 2:
- Conclusion:
- Remaining uncertainty:
- Prevention:
