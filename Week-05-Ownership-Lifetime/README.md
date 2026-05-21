# Week 5 - Ownership and Lifetime

## Investigation

You have a set of tiny failures around ownership and lifetime. The assignment is not to memorize Valgrind output. The assignment is to reconstruct the responsibility story from the report: who created the thing, who owned it, who changed it, who should have cleaned it up, and who used it after the contract was broken.

In memory code, that story is about bytes, allocation, initialization, and cleanup. In other systems, it may be about files, handles, jobs, transactions, cache entries, sessions, or database rows.

## Mentor Opening

- What memory contract do you think the program violated?
- What would an invalid write prove that a leak report would not?
- What allocation or lifetime question should the first run answer?
- What line in a report would connect the symptom to the allocation site?
- What would you inspect if the report points into helper code?

## First Claim

Before running the evidence tool, write:

```text
Claim:
Confidence:
Bug class I expect:
Report field I expect to matter:
Evidence that would weaken this:
```

## Evidence Round 1

Build and run the first target:

```bash
cd Week-05-Ownership-Lifetime/example
make clean
make
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./01_heap_overflow
```

Record:

- the error category
- the bad access line
- the allocation site
- whether the memory was unallocated, freed, uninitialized, or leaked
- why Memcheck knows

## Mentor Interruption

- Which bytes were invalid, missing, or uninitialized?
- Did the report identify the bad use, the bad allocation, or both?
- What is direct report evidence?
- What ownership story are you inferring?
- What code-review pattern would have caught this earlier?

## Evidence Round 2

Run a contrasting target under the same flags:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./04_uninitialized
```

or:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07_leak
```

Before running, predict the category. After running, write what changed in your ownership or initialization model.

## Debrief

Valgrind is slow because it is watching memory closely. Use that cost to answer precise ownership questions. In other stacks, use the closest equivalent: heap snapshots, resource leak detectors, transaction logs, job histories, cache traces, or lifecycle instrumentation. A good report reading connects bad use, creation site, initialization state, ownership transfer, and cleanup path.

The report is not the final explanation. It is the evidence that lets you reconstruct the explanation.

## Apprentice Notes

Write one note:

```text
Symptom:
Expected bug class:
Valgrind command:
Report evidence:
Ownership model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- classify the report correctly
- name both bad-use and allocation evidence when present
- explain initialized versus allocated memory
- distinguish "definitely lost" from reachable memory when leaks appear
- propose a prevention pattern such as clearer ownership, cleanup paths, or bounds checks

Weak answers:

- say "the tool found a bug" without naming the category or evidence
- ignore allocation-site evidence
- fix the symptom without explaining ownership
- suppress reports before understanding them
