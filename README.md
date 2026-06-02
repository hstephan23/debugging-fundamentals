# Debugging Thinking Apprenticeship

A mentor-led curriculum for learning how to approach software failures through investigation, critical thinking, evidence, and postmortems.

This is not a tour of C, GDB, or any single toolchain. Each week starts with a failure shape and asks the learner to make a claim, identify evidence, interpret what that evidence would prove, and revise the model.

## Who This Is For

Use this repo if:

- you want to learn debugging as a repeatable thinking discipline
- you have a mentor, study partner, or review group that can challenge your reasoning
- you are willing to answer precise prompts instead of jumping to fixes
- you want discussion material that transfers across languages, systems, and tools

Solo learners can still use the repo. Read the mentor prompts out loud, answer them in your bug journal, and do not continue until you can name the evidence that would change your mind.

## What You Are Practicing

The curriculum is built around habits that transfer across languages, frameworks, and runtimes:

- turn vague symptoms into specific, observable questions
- separate what happened from why you think it happened
- make hypotheses that can be weakened, not just confirmed
- choose the smallest question that can reduce uncertainty
- preserve evidence before changing the system
- compare alternative explanations instead of chasing the first plausible story
- end with a prevention move: test, assertion, invariant, log, type, monitor, review rule, or design change

## How Sessions Work

Every module follows the same loop:

1. Restate the symptom.
2. Make a first claim.
3. Name what would weaken that claim.
4. Choose the smallest useful question or evidence source.
5. Separate direct evidence from interpretation.
6. Update the model.
7. Ask a narrower follow-up question.
8. End with a prevention or postmortem note.

The learner should leave each session with a short note:

```text
Symptom:
First claim:
Question or evidence source:
Evidence:
Model update:
Next move:
Prevention:
```

## Shared Guides

- [Mentor Guide](mentor-guide.md): how to run sessions, interrupt guesses, and demand evidence.
- [Learner Guide](learner-guide.md): how to prepare, answer, and keep a useful bug journal.
- [Investigation Template](investigation-template.md): the canonical structure for future modules.
- [Discussion Rubric](discussion-rubric.md): how to evaluate debugging reasoning.

## The Core Rule

Do not say a tool found the bug. Say what evidence changed your model.

Use this shape instead:

```text
I believed:
The evidence showed:
That changed:
The next question is:
```

## The 10 Investigations

| Week | Module | Apprenticeship Focus |
|---|---|---|
| 1 | [Foundations](Week-01-Symptoms-Inputs-Claims/README.md) | Turn symptoms into testable hypotheses. |
| 2 | [Runtime State](Week-02-Runtime-State/README.md) | Stop at useful boundaries and inspect live state. |
| 3 | [Causality](Week-03-Causality/README.md) | Trace where state first changed, not only where it was noticed. |
| 4 | [Preserve Failure Evidence](Week-04-Preserve-Failure-Evidence/README.md) | Preserve evidence before changing the system. |
| 5 | [Reconstruct Responsibility](Week-05-Reconstruct-Responsibility/README.md) | Identify who owned, changed, or inherited broken state. |
| 6 | [Reason From Guardrails](Week-06-Reason-From-Guardrails/README.md) | Use checks and violated boundaries as evidence. |
| 7 | [Unreliable Outcomes](Week-07-Unreliable-Outcomes/README.md) | Separate variable outcomes from defensible causes. |
| 8 | [Stuck Systems](Week-08-Stuck-Systems/README.md) | Inspect blocked systems without destroying live evidence. |
| 9 | [Choose Useful Signals](Week-09-Choose-Useful-Signals/README.md) | Select the least disruptive evidence source for the question. |
| 10 | [Defend The Investigation](Week-10-Defend-The-Investigation/README.md) | Turn an investigation into a defensible conclusion. |

## Discussion Policy

Weeks 04-10 are discussion-first. They should contain questions, prompts, reasoning structures, and note templates, not runnable examples or tool walkthroughs.

Use real incidents, remembered bugs, production reports, test failures, support tickets, local project failures, or hypothetical failure shapes as the discussion material. Keep any pseudocode minimal and use it only to clarify a state transition or decision point.

## Mentor Expectations

The mentor should:

- ask for the learner's hypothesis before choosing evidence
- interrupt vague answers
- ask what would disprove the claim
- force one-variable reasoning
- ask what the evidence showed directly
- end with prevention

The mentor should not:

- lecture through all concepts before the first observation
- accept "the tool found it" as an explanation
- let the learner keep changing the system without naming evidence
- treat one passing concurrent run as proof

## Learner Expectations

The learner should:

- write short notes
- give confidence levels
- separate evidence from inference
- revise the model when evidence changes
- explain why the next question is smaller or sharper
- name how this bug could be easier to catch next time

## Evidence Sources

Use whatever evidence source fits the system under discussion:

- browser devtools, server logs, traces, metrics, database query logs
- failing tests, property checks, type errors, lint output
- request IDs, queue events, job histories, deployment diffs
- debugger breakpoints, profiles, heap snapshots, crash reports
- support tickets, screenshots, audit logs, feature flags, configuration history
