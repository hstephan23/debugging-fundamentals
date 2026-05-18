# Week 10 - Capstone

## Investigation

Choose one failure shape: crash, hang, memory corruption, concurrency, or slowness. Your job is to run a complete investigation and defend the postmortem.

This week is not about using every tool. It is about choosing a playbook, producing evidence, and explaining why your conclusion follows.

## Mentor Opening

- What kind of failure is this?
- Which playbook from `playbooks.md` applies first?
- What evidence must be preserved before changing anything?
- What would make your first theory false?
- What prevention step would make this easier next time?

## First Claim

Before choosing tools, write:

```text
Failure class:
Claim:
Confidence:
First playbook:
Evidence that would support this:
Evidence that would weaken this:
```

## Evidence Round 1

Pick one previous example or a small C program of your own. Start with one playbook:

```bash
sed -n '1,220p' Week-10-Capstone/playbooks.md
```

Then run the first tool the playbook recommends. Examples:

```bash
gdb ./program ./core
valgrind --leak-check=full --track-origins=yes ./program
./program
gdb -p <pid>
perf record -g ./program
```

Record the strongest piece of evidence and the claim it changes.

## Mentor Interruption

- Why did you choose that playbook?
- What evidence did you preserve?
- What did the tool show directly?
- What are you inferring?
- What remains unproven?

## Evidence Round 2

Run one narrower experiment. It must reduce uncertainty from Round 1.

Examples:

```bash
# inspect a caller frame after the crash-site frame
gdb ./program ./core
```

```bash
# compare sanitizer evidence with Valgrind evidence
make asan
./program
```

```bash
# compare a suspected race with a synchronized version
./race_counter
./race_counter_mutex
```

Write whether the second experiment supports, weakens, or redirects your model.

## Debrief

Produce a short postmortem:

- symptom
- reproducer or preserved artifact
- investigation path
- strongest evidence
- root cause or best current theory
- false lead avoided
- prevention step

The mentor should challenge any sentence that does not connect to evidence.

## Apprentice Notes

Write the final note:

```text
Failure class:
First claim:
Evidence round 1:
Model update:
Evidence round 2:
Conclusion:
Prevention:
```

## Mentor Rubric

Strong answers:

- choose a playbook from the symptom
- preserve evidence before changing state
- explain why each tool was chosen
- make a conclusion proportional to the evidence
- include a concrete prevention step

Weak answers:

- use every tool without a question
- skip the artifact or reproducer
- write a postmortem that starts with the fix instead of the evidence
- claim certainty when the investigation only supports a theory
