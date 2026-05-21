# Discussion Rubric

Use this rubric to evaluate the learner's debugging conversation. The score matters less than the pattern of weakness.

## 4 - Strong

The learner:

- states a testable hypothesis before using tools
- names direct evidence precisely
- separates observation from interpretation
- changes one variable at a time
- updates the model when evidence changes
- chooses the next experiment from the current evidence
- ends with a prevention idea

Example:

> I thought the crash came from recursion depth. In frame 0, `n` is already negative before the recursive call, so the bad state crossed the function boundary. I need to inspect the caller, not keep stepping deeper.

## 3 - Solid

The learner:

- has a plausible hypothesis
- uses a relevant tool
- identifies useful evidence
- explains the next move, but may blur evidence and inference

Example:

> The trace shows the request crossed the API boundary with a tenant ID, but the database query ran without that filter. I think the repository method dropped context, so I will inspect the query builder inputs.

## 2 - Shallow

The learner:

- follows commands but cannot explain why that experiment was chosen
- names the tool instead of the evidence
- jumps from symptom to cause too quickly
- needs mentor help to choose the next experiment

Example:

> The debugger says it crashed in `parse`.

The missing part is what value, frame, input, state transition, or source line made `parse` suspicious.

## 1 - Guessing

The learner:

- makes root-cause claims without evidence
- changes several things at once
- treats one passing run as proof
- ignores contradictory output
- cannot say what would disprove the current theory

Example:

> It is probably a framework bug because local mode works.

The claim might be possible, but the learner has not tested configuration, input, dependency versions, data shape, timing, or environment.

## Mentor Response By Score

For a 4:

- ask for the prevention step
- ask how they would teach the playbook to someone else

For a 3:

- ask them to restate the direct evidence without interpretation
- ask for one falsifying observation

For a 2:

- stop the tool sequence
- return to symptom, hypothesis, experiment, evidence

For a 1:

- require a written first claim before any more commands
- allow only one variable to change in the next experiment

## Evidence Checklist

A good answer includes at least three of these:

- command or action
- observed output
- relevant line, value, frame, report, or log entry
- hypothesis before the command
- confidence change after the command
- next experiment
- prevention step
