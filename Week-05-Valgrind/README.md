# Week 5 - Valgrind

## Investigation

You have a bug buffet: one tiny C program per memory failure class. The assignment is not to memorize Valgrind output. The assignment is to reconstruct the ownership and lifetime story from the report.

Every Memcheck report is asking: was this byte allocated, initialized, and still owned by this code path?

## Mentor Opening

- What memory contract do you think the program violated?
- What would an invalid write prove that a leak report would not?
- What allocation or lifetime question should the first run answer?
- What line in a report would connect the symptom to the allocation site?
- What would you inspect if the report points into helper code?

## First Claim

Before running Valgrind, write:

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
cd Week-05-Valgrind/example
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

Valgrind is slow because it is watching memory closely. Use that cost to answer precise ownership questions. A good report reading connects bad access, allocation site, initialization state, and cleanup path.

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

- say "Valgrind found a bug" without naming the category
- ignore allocation-site evidence
- fix the symptom without explaining ownership
- suppress reports before understanding them
