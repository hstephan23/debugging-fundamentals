# Week 6 - Reason From Guardrails

## Discussion Goal

Use runtime checks as evidence about violated boundaries without confusing a precise failure report for a complete explanation.

## Opening Prompts

- What boundary should have protected this state?
- What invariant appears to have been crossed?
- What check would fail closest to the bad operation?
- What check would fail closest to the design mistake?
- What would a runtime report prove directly, and what would it leave unexplained?

## First Claim Prompts

- What invalid state do you expect a runtime check to expose?
- How confident are you?
- What exact boundary do you expect to fail?
- What evidence would show the check is only catching a downstream symptom?
- What evidence would make you inspect an earlier design decision?

## Evidence Interpretation Prompts

- What did the check observe directly?
- Was the observed failure about bounds, shape, type, lifetime, permission, ordering, timing, or an impossible state?
- Which earlier decision allowed the invalid state to become reachable?
- Which caller, input, dependency, or state transition should have rejected it earlier?
- What would the system have done without the runtime check?

## Mentor Interruption Prompts

- Are you stopping at the report because it feels precise?
- What was the bad operation?
- What was the bad assumption?
- What boundary should have made that operation impossible?
- What result would make the report misleading or incomplete?

## Model Update Prompts

- Which invariant is now proven broken?
- Which root-cause theory is still only inferred?
- What would distinguish a local coding mistake from a design-level contract failure?
- What narrower question should be asked next?
- What evidence would make you move the check closer to the source?

## Prevention Prompts

- What assertion, validation, schema, type, permission check, invariant check, or safety rail belongs in the system?
- Should the prevention live at the boundary, in the core model, or in tests?
- What should happen when the check fails?
- How would the failure be reported to make the next investigation shorter?
- What class of invalid states should become unrepresentable?

## Apprentice Note Prompts

- Symptom:
- Violated boundary:
- First claim:
- Runtime evidence:
- Operation that failed:
- Earlier assumption:
- Model update:
- Prevention:
