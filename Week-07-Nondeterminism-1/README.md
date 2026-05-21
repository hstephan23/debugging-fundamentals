# Week 7 - Nondeterminism I

## Investigation

A counter program prints different answers across runs. Sometimes it looks close to correct. Sometimes it is far off. A single passing run means almost nothing.

This week is about making nondeterminism observable and separating repeated symptoms, race-detector evidence, and actual synchronization or ordering rules.

## Mentor Opening

- What shared state exists?
- Which threads read or write it?
- What would make the final value nondeterministic?
- What evidence would prove a data race rather than only a timing-dependent outcome?
- Why is "it passed once" weak evidence?

## First Claim

Before running the race detector, write:

```text
Claim:
Confidence:
Shared state I suspect:
Accesses that might race:
Evidence that would weaken this:
```

## Evidence Round 1

Build and run the plain program more than once:

```bash
cd Week-07-Nondeterminism-1/example
make clean
make
./race_counter
./race_counter
./race_counter
```

Record:

- each final count
- expected count
- whether the symptom is deterministic
- which shared variable appears involved

## Mentor Interruption

- What did repeated runs prove?
- Did they prove the exact race?
- What shared memory location needs an ownership rule?
- What synchronization is missing?
- What evidence would be stronger than differing final counts?

## Evidence Round 2

Run ThreadSanitizer and compare fixed versions:

```bash
make tsan
./tsan_race
./race_counter_mutex
./race_counter_atomic
```

Record:

- both access stacks from the TSan report
- which access is a write
- whether synchronization exists between them
- how the mutex and atomic versions change the evidence

## Debrief

Nondeterministic bugs punish casual proof. A clean investigation names the shared state or shared resource, identifies the conflicting operations, and explains the ownership, ordering, or synchronization rule that removes the failure.

The fix is not "make this run pass." The fix is a durable ownership or happens-before rule.

## Apprentice Notes

Write one note:

```text
Symptom:
First claim:
Repeated-run evidence:
TSan evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- separate nondeterministic output from race-detector evidence
- name the shared variable
- identify both racing stacks
- explain mutex versus atomic fixes
- avoid treating one passing run as proof

Weak answers:

- say "threads are flaky"
- trust the fixed output without explaining synchronization
- ignore one of the two TSan stacks
- confuse a data race with any timing-dependent bug
