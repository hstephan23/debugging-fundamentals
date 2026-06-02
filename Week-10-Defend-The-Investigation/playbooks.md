# Debugging Thinking Playbooks

These playbooks are short enough to read under pressure. Use them as discussion prompts for deciding what evidence matters and why.

---

## A process crashed

- What artifact captures the failure closest to the moment it happened?
- What input, version, environment, or user action must be preserved with it?
- What failure point is probably the symptom rather than the cause?
- What state would let you inspect the path into the failure?
- What must be written in the bug journal before anyone starts fixing?

---

## A process hung

- What proves this is hung rather than slow?
- What live state can be preserved before disturbing the system?
- Which actors are waiting?
- What resource or dependency does each actor need?
- Is there a cycle, missing wakeup, saturated pool, stuck dependency, or long operation?

---

## Memory is corrupting

- What resource or state appears corrupted?
- What boundary should have protected it?
- What evidence would identify the first invalid write, mutation, transfer, or stale read?
- What narrower input, actor set, or deterministic condition would reduce uncertainty?
- What contract allowed the corrupted state to become reachable?

---

## Concurrency is suspicious

- What outcome changes across attempts?
- What shared resource, schedule, queue, clock, cache, or dependency might affect it?
- Which actors can read or write the shared state?
- What ordering or ownership rule should make the behavior deterministic?
- What evidence would identify conflicting operations rather than merely unreliable outcomes?

---

## It's slow (performance as debugging)

- What does "slow" mean in observable terms?
- What baseline would make the complaint measurable?
- Where is time expected to be spent?
- What evidence would identify the actual bottleneck?
- What would prevent optimizing a part of the system that is not on the critical path?

---

## Output is wrong

- What exact input, output, expected output, and environment define the failure?
- Where can expected and actual state first be compared?
- Did the bad state enter through input, transformation, persistence, cache, dependency, or rendering?
- What is the first boundary where the state diverges?
- What prevention belongs at the boundary where the invariant first broke?

---

## An integration failed

- What request IDs, payload shape, status codes, retries, timestamps, and version or configuration differences matter?
- Which side owns the contract: caller, callee, transport, auth, schema, or environment?
- What known-good path can be compared with the failing path?
- What is the first boundary where the two diverge?
- What prevention would make the contract failure impossible or obvious?
