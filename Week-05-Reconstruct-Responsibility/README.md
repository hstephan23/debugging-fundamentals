# Week 5 - Reconstruct Responsibility

## Discussion Goal

Practice reconstructing responsibility: who created a thing, who owned it, who changed it, who should have cleaned it up, and who used it after the contract was broken.

## Scenario Packet

An operations team reports that several users received **Your export is ready** emails for reports they had already cancelled. The links in the emails still opened valid CSV files for about 20 minutes.

Known facts:

- The issue was reported at 14:06.
- The affected export jobs were created between 13:38 and 13:46.
- The export flow creates an `export_jobs` row with status `queued`.
- The export worker leases a queued job by setting `locked_by` and `lock_expires_at`.
- The user can cancel an export from the UI.
- Cancelling an export changes the `export_jobs` status to `cancelled`.
- A cleanup job deletes files for cancelled exports after 15 minutes.
- The database row remains for 24 hours for audit history.
- The worker checks job status when it first leases the job.
- The worker does not check job status again before uploading the CSV file or sending the email.
- A deploy at 13:30 changed the cancel button to retry automatically if the cancel request times out.
- Logs show job `8021` was leased by `worker-a` at 13:42.
- Logs show job `8021` was marked `cancelled` by the cancel API at 13:43.
- Logs show `worker-a` uploaded `job-8021.csv` at 13:49.
- Logs show the email service sent the ready email at 13:50.
- The cleanup job deleted `job-8021.csv` at 14:05.

Current pressure:

- Support wants to know whether users received files they should not have received.
- Operations wants to disable exports until the cause is known.
- Engineering wants to know whether the retrying cancel button caused the problem.
- Compliance wants to know which actor was responsible for the file remaining readable.

The learner should not fix the bug yet. The learner's job is to reconstruct the responsibility story: who created the export job, who owned it while it was leased, what changed when the user cancelled it, who should have observed that change, who should have cleaned up the file, and who used the state after the contract was already broken.

## Opening Prompts

- What resource, value, object, record, session, handle, job, or transaction appears to have the wrong lifetime?
- Who creates it?
- Who is allowed to mutate it?
- Who is responsible for releasing, closing, committing, expiring, or invalidating it?
- Who observed it after the contract had already been broken?

## Scenario Discussion Prompts

- Which parts of the export flow create new state, and which parts only observe existing state?
- When the user cancelled the export, what responsibility should have transferred or ended?
- Which actor had enough information to stop the ready email?
- Which actor merely inherited state that was already invalid?
- What does the cleanup job prove directly, and what does it fail to prove?
- What evidence would show whether the cancel-button retry caused duplicate cancellation requests or only made an existing ownership rule easier to violate?

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

## Candidate Responsibility Stories

Use these only as starting points to challenge:

- The worker owns a leased export until completion, so it should re-check cancellation before publishing or emailing.
- The cancel API owns cancellation, so it should revoke the worker lease or mark the job in a way the worker cannot ignore.
- The cleanup job owns file lifetime, so it should delete cancelled export files before they can be sent.
- The email service is only the messenger because it sent exactly what the worker requested.
- The retrying cancel button exposed the bug by making cancellation timing more likely, but it did not own the publish decision.

For each story, ask:

- What evidence would support it?
- What evidence would weaken it?
- What event marks the first broken responsibility boundary?
- Which actor had enough context to prevent the invalid use?

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
