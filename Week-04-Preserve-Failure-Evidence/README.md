# Week 4 - Preserve Failure Evidence

## Discussion Goal

Use a failure that already happened to practice preserving evidence before changing the system.

## Scenario Packet

A customer-support team reports that several users were charged twice after clicking **Place order** once. The duplicate charges appear to have happened during a short payment-provider slowdown.

Known facts:

- The issue was reported at 10:42.
- The affected orders were created between 10:18 and 10:27.
- The payment provider status page shows elevated latency from 10:15 to 10:31.
- The application team deployed a checkout retry change at 09:55.
- Support has three user screenshots showing one confirmation page but two bank authorization rows.
- The order database currently shows one order record for each affected user.
- The payment provider dashboard currently shows two authorization events for each affected user.
- The checkout service logs are retained for 24 hours.
- Payment-provider webhook payloads are retained for 7 days.
- A cleanup job runs every hour and removes abandoned checkout sessions.
- A developer wants to "just retry the checkout flow locally" to see whether it still happens.

Current pressure:

- Support wants a customer-facing answer.
- Finance wants to know whether to void charges immediately.
- Engineering wants to know whether the retry change caused the duplicate authorizations.
- Product wants checkout restored to normal before the next traffic spike.

The learner should not solve the bug yet. The learner's job is to decide what evidence must be preserved before anyone retries, rolls back, edits code, voids charges, clears sessions, or tells customers a cause.

## Opening Prompts

- What failed, and how do you know it failed?

  I think what failed is the retry mechanism. The reason I believe that is what failed is that it was released right before the failure. They probably didn't test the feature in low latency to see if it would double send. 

- What evidence exists right now that might disappear if you restart, retry, clean up, deploy, or edit?

  It depends on the system, I'm not entirely certain. I think in this case nothing? Besides the stale checkout pieces... It doesn't really mention in the prompt

- What part of the current state is evidence, and what part is interpretation?

  I think the current evidence is the code push and low bandwidth, the rest is mostly interpretation of the event. 

## Scenario Discussion Prompts

- Which facts are direct evidence, secondhand reports, or timing coincidences?

  I think some of these are difficult to answer without knowing the exact tech stack and build of each user. I'm also not good at determining this... I get caught up too much in the fine details.  

- Which evidence is most likely to disappear first?

  The stale checkout sessions (if they exist).

- What could be changed or hidden by retrying checkout, voiding charges, clearing sessions, or waiting until tomorrow?

  A lot of data could be erased per the instructions. Maybe the dual charges will be automatically sorted out by the bank. Waiting too long can make reproducing the issue more difficult. 

- What would you preserve from support, finance, engineering, and the payment provider before changing anything?

  I would get an exact replicate of the Production code base, copy of DB, and then all the notes mentioned above. 

- What should be included in the first incident note without claiming root cause?

  I think the first inclusion is that this will be resolved and customers can be assured their charges will be correct. I think stating only facts of what you have determined so far is important too. 


## First Claim Prompts

- What is your first explanation for the failure?

  I think what failed is the retry mechanism. The reason I believe that is what failed is that it was released right before the failure. They probably didn't test the feature in low latency to see if it would double send. 

- How confident are you?

  Not very. 

- What preserved artifact would support that explanation?

  The recent code push. 

- What preserved artifact would weaken it?

  The fact that the latency happened longer than the reported failures did. 

## Candidate First Claims

Use these only as starting points to challenge:

- The checkout retry change sent the same payment request twice.
- The payment provider duplicated authorization events during its latency window.
- Users double-clicked or refreshed even though support screenshots show one confirmation page.
- The app created one order but processed two payment webhooks.
- The issue is a reporting mismatch: the bank shows two authorizations, but only one will settle.

For each claim, ask:

- What evidence would support it?
- What evidence would weaken it?
- What evidence would distinguish this claim from the next most plausible claim?

## Evidence Quality Prompts

- Which artifact is closest to the moment of failure?
- Which facts are missing from the failure report?
- What context would make the artifact readable to someone else?

## Mentor Interruption Prompts

- What have you preserved before touching the system?
- What would be destroyed by a casual rerun?
- Are you treating the first visible symptom as the cause?

## Model Update Prompts

- What did the preserved evidence show directly?
- What did it fail to show?
- Which part of your first claim became stronger or weaker?
- What narrower question should the next evidence source answer?

## Prevention Prompts

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
