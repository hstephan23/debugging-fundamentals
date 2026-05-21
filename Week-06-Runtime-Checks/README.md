# Week 6 - Runtime Checks

## Investigation

The same small examples are rebuilt with runtime instrumentation. Sanitizers usually fail loudly and near the bad operation. Your job is to turn that precise failure into a root-cause investigation without stopping at the report.

This week is about using sharp evidence without becoming lazy about explanation. The broader pattern applies to assertions, contract checks, type guards, schema validation, invariant checks, and production safety rails.

## Mentor Opening

- What kind of undefined behavior do you expect?
- What does a sanitizer report prove directly?
- What does it not prove by itself?
- How would you distinguish the bad operation from the design mistake that allowed it?
- When would you choose ASan before Valgrind, or Valgrind before ASan?

## First Claim

Before running the sanitizer builds, write:

```text
Claim:
Confidence:
Sanitizer I expect to be most useful:
Report field I expect to matter:
Evidence that would weaken this:
```

## Evidence Round 1

Build and run the AddressSanitizer target:

```bash
cd Week-06-Runtime-Checks/example
make clean
make asan
./asan_demo
```

Record:

- sanitizer name
- failure category
- access size
- source line
- allocation or shadow-memory clue
- whether execution stopped immediately

## Mentor Interruption

- What operation failed?
- What source line did the report identify?
- What earlier design choice made that operation possible?
- Is this a bounds, lifetime, initialization, or API-contract problem?
- What would a test or assertion need to catch this sooner?

## Evidence Round 2

Build and run the UndefinedBehaviorSanitizer target:

```bash
make ubsan
./ubsan_demo
```

Compare the two reports:

- Which one points closer to the bad operation?
- Which one requires more interpretation?
- What would you rerun with different sanitizer flags?
- What result would make you inspect compiler optimization or integer assumptions?

## Debrief

Runtime checks are excellent at turning hidden invalid states into concrete evidence. They are not a substitute for reasoning about invariants. Use the report to locate the violated boundary, then ask why the system allowed that boundary to be crossed.

## Apprentice Notes

Write one note:

```text
Symptom:
First claim:
Sanitizer command:
Report evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- name the sanitizer and failure category
- quote the meaningful source line or access detail
- distinguish failing operation from root cause
- compare ASan and UBSan evidence
- propose a prevention step such as bounds validation, invariant checks, schema checks, assertions, or runtime-check CI

Weak answers:

- stop at "ASan crashed"
- copy the report without interpreting it
- treat sanitizer output as a complete postmortem
- ignore why the invalid operation was reachable
