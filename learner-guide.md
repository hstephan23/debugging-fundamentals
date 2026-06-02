# Learner Guide

This repo teaches debugging through apprenticeship. You will be asked to make claims, choose evidence, interpret that evidence, and revise your model out loud.

The point is not to sound certain. The point is to become precise.

## How To Prepare

Before a session:

- open the week's `README.md`
- create or open your bug journal
- expect to answer in short notes, not essays

Bring a willingness to be wrong in public. A wrong hypothesis weakened cleanly is progress.

## How To Answer

Use this shape:

```text
I think <claim> because <reason>.
I am <low/medium/high> confidence.
This would be weaker if <specific observation>.
The next question is <question>.
```

After the evidence discussion:

```text
I observed <exact evidence>.
That changes <hypothesis> because <reason>.
The next smallest question is <next question>.
```

## What Counts As Evidence

Good evidence is something the system showed directly. It can come from a program, diagnostic report, test, runtime, operating system, service, database, browser, log pipeline, or user-visible artifact:

- a stack frame
- an argument value
- a local variable
- a failing assertion or test case
- a trace span or request ID
- a database row or query plan
- a network status code or payload
- a heap snapshot or allocation site
- a runtime check report line
- a thread state
- a log entry
- a syscall trace
- a repeated output difference
- a deployment, configuration, or environment difference

Your interpretation comes after the evidence. Keep those separate.

## Bug Journal Format

Use this for every investigation:

```text
Symptom:
First hypothesis:
Confidence:
Experiment:
Evidence:
Update:
Next move:
Prevention:
```

Keep entries short. A useful entry usually fits on one screen.

## What To Do When Stuck

If you are stuck, do not read more randomly. Write three lists:

```text
Known:
Assumed:
Unknown:
```

Then pick one unknown and ask what single observation, input change, boundary check, log line, artifact, or question could answer it.

## Strong Habits

- Change one variable at a time.
- Prefer evidence over explanation.
- Stop after three failed hypotheses and rebuild the model.
- Treat environment, configuration, timing, input, and diagnostic versions as possible inputs.
- Ask what would prevent the bug, not only what caused it.
- Write down the observation that would make your current theory weaker.
- Make the next question smaller than the current uncertainty.
