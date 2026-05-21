# Learner Guide

This repo teaches debugging through apprenticeship. You will be asked to make claims, run experiments, interpret evidence, and revise your model out loud.

The point is not to sound certain. The point is to become precise.

## How To Prepare

Before a session:

- open the week's `README.md`
- build the example if the week asks you to
- create or open your bug journal
- expect to answer in short notes, not essays

Bring a terminal and a willingness to be wrong in public. A wrong hypothesis tested cleanly is progress.

## How To Answer

Use this shape:

```text
I think <claim> because <reason>.
I am <low/medium/high> confidence.
This would be weaker if <specific observation>.
I will run <command/action> to check <question>.
```

After the experiment:

```text
I observed <exact evidence>.
That changes <hypothesis> because <reason>.
The next smallest experiment is <next action>.
```

## What Counts As Evidence

Good evidence is something the system showed directly. It can come from a program, tool, test, runtime, operating system, service, database, browser, log pipeline, or user-visible artifact:

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

Then pick one unknown and ask what single command, input change, build change, or log line could answer it.

## Strong Habits

- Change one variable at a time.
- Prefer evidence over explanation.
- Stop after three failed hypotheses and rebuild the model.
- Treat environment, build flags, timing, input, and tool versions as possible inputs.
- Ask what would prevent the bug, not only what caused it.
- Write down the observation that would make your current theory weaker.
- Make the next experiment smaller than the current uncertainty.
