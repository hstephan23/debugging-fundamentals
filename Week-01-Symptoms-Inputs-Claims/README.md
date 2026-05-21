# Week 1 - Foundations: Symptoms, Inputs, and Claims

## Investigation

The same code behaves differently under two build modes. In one mode, the program is expected to trip an assertion. In the other, the assertion is compiled out, so the symptom changes.

Your task is not to guess which build is "real." Your task is to treat build mode, configuration, environment, and input as part of the system and explain what each run proves.

## Mentor Opening

- What failed, and how do you know?
- What are the inputs besides the obvious program input?
- What is your first hypothesis about why the two builds differ?
- What observation would make that hypothesis weaker?
- What is the smallest build or run experiment that can produce evidence?

## First Claim

Before running commands, write:

```text
Claim:
Confidence:
Build input I think matters:
Evidence that would support this:
Evidence that would weaken this:
```

Do not use "debug build" or "release build" as an explanation by itself. Name the specific flag, runtime check, optimization behavior, configuration value, or hidden input you think matters.

## Evidence Round 1

Build and run both modes:

```bash
cd Week-01-Symptoms-Inputs-Claims/example
make clean
make debug
make release
make run-debug
make run-release
```

Record:

- which command failed or produced surprising output
- whether the result came from the program, the shell, `make`, or an assertion
- what changed between the two runs
- what stayed constant

## Mentor Interruption

- What did the terminal show directly?
- Which part is evidence, and which part is your interpretation?
- Did the source change between runs?
- Which compiler flags changed?
- If the assertion is compiled out, does that mean the bug is gone?

## Evidence Round 2

Inspect the build rules:

```bash
sed -n '1,180p' Makefile
```

Then answer:

- Which flags support debugging?
- Which flags make the binary closer to a shipped build?
- Which flag removes assertions?
- Which warnings, assertions, checks, or validations would you keep in every project?

## Debrief

This week is about controlled learning. Debugging starts by naming the symptom and changing one variable at a time. Build flags, configuration, environment, data, timing, and input are part of the bug surface.

The important lesson is not that debug builds are good and release builds are bad. The lesson is that different builds answer different questions.

## Apprentice Notes

Write one note:

```text
Symptom:
First claim:
Experiment:
Evidence:
Model update:
Next move:
Prevention:
```

## Mentor Rubric

Strong answers:

- name the exact build difference
- separate assertion behavior from root cause
- explain why one run does not invalidate the other
- identify at least one useful warning, assertion, check, or validation
- propose a next experiment that changes one variable

Weak answers:

- say "release fixed it"
- say "debug is broken" without naming evidence
- ignore compiler flags
- change source code before explaining the run results
