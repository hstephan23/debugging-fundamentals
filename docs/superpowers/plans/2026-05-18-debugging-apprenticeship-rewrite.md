# Debugging Apprenticeship Rewrite Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Rework the repository into a C-specific mentor-led debugging apprenticeship built around discussion, evidence, and defended hypotheses.

**Architecture:** The rewrite is documentation-first. Shared top-level guides define the apprenticeship model, while each weekly README becomes a self-contained investigation using the same mentor dialogue structure. Existing C `example/` directories remain the practice substrate unless verification shows a source file is missing or unusable.

**Tech Stack:** Markdown curriculum files, existing C examples, Makefiles/CMake files, Git.

---

## File Structure

- Create `mentor-guide.md`: mentor operating model, session rhythm, interruption patterns, and review rules.
- Create `learner-guide.md`: expectations for apprentice answers, bug journal style, and how to prepare for sessions.
- Create `investigation-template.md`: reusable weekly structure for future modules.
- Create `discussion-rubric.md`: concrete rubric for evaluating claims, evidence, tool choice, model updates, and prevention.
- Modify `README.md`: repo identity, how to use the apprenticeship, week map, shared guide links, and example-code policy.
- Modify `Week-01-Symptoms-Inputs-Claims/README.md`: scenario about debug vs release behavior and hypothesis discipline.
- Modify `Week-02-Runtime-State/README.md`: scenario about choosing breakpoints and reading stack/local state.
- Modify `Week-03-Causality/README.md`: scenario about tracing who changed suspicious state.
- Modify `Week-04-Postmortem-Evidence/README.md`: scenario about preserving postmortem evidence after a crash.
- Modify `Week-05-Ownership-Lifetime/README.md`: scenario about reconstructing memory ownership from Memcheck reports.
- Modify `Week-06-Runtime-Checks/README.md`: scenario about interpreting sanitizer failures as precise evidence.
- Modify `Week-07-Nondeterminism-1/README.md`: scenario about nondeterministic counters and TSan evidence.
- Modify `Week-08-Nondeterminism-2/README.md`: scenario about deadlock and live-thread inspection.
- Modify `Week-09-Signals-Observability/README.md`: scenario about debugging from logs, traces, and profiles.
- Modify `Week-10-Full-Investigation/README.md`: final mentor-led investigation and postmortem defense.
- Inspect tracked binaries under `Week-*/example/`: remove from Git only if they are tracked compiled artifacts; preserve source files and build files.

## Task 1: Shared Apprenticeship Guides

**Files:**
- Create: `mentor-guide.md`
- Create: `learner-guide.md`
- Create: `investigation-template.md`
- Create: `discussion-rubric.md`

- [ ] **Step 1: Write the four shared guides**

  Create the guides with these exact responsibilities:

  - `mentor-guide.md`: how the mentor runs a session, when to interrupt, how to force evidence over guesses, how to end a session.
  - `learner-guide.md`: how the apprentice should prepare, answer, record evidence, and handle wrong hypotheses.
  - `investigation-template.md`: the canonical weekly module skeleton.
  - `discussion-rubric.md`: a scored rubric with strong/weak examples.

- [ ] **Step 2: Verify guide links and style**

  Run:

  ```bash
  sed -n '1,220p' mentor-guide.md
  sed -n '1,220p' learner-guide.md
  sed -n '1,220p' investigation-template.md
  sed -n '1,240p' discussion-rubric.md
  ```

  Expected: each file has a clear title, no placeholders, and no references to missing files.

- [ ] **Step 3: Commit shared guides**

  Run:

  ```bash
  git add mentor-guide.md learner-guide.md investigation-template.md discussion-rubric.md
  git commit -m "Add debugging apprenticeship guides"
  ```

## Task 2: Top-Level README Rewrite

**Files:**
- Modify: `README.md`

- [ ] **Step 1: Rewrite the README around the new identity**

  Replace the old self-directed curriculum framing with:

  - project title: `Debugging Apprenticeship`
  - one-paragraph purpose
  - who should use it
  - how mentor-led sessions work
  - how solo learners can use the prompts
  - links to the four shared guides
  - week map with apprenticeship focus
  - example-code policy
  - expected session artifact: a short investigation note

- [ ] **Step 2: Verify README structure**

  Run:

  ```bash
  sed -n '1,260p' README.md
  ```

  Expected: the README links to all four shared guides and all ten weeks.

- [ ] **Step 3: Commit README rewrite**

  Run:

  ```bash
  git add README.md
  git commit -m "Rewrite README for debugging apprenticeship"
  ```

## Task 3: Weeks 1-3 Dialogue Rewrites

**Files:**
- Modify: `Week-01-Symptoms-Inputs-Claims/README.md`
- Modify: `Week-02-Runtime-State/README.md`
- Modify: `Week-03-Causality/README.md`

- [ ] **Step 1: Rewrite Week 1**

  Use the canonical weekly sections:

  - Investigation: debug vs release behavior differs.
  - Mentor Opening: symptom, hidden inputs, first hypothesis.
  - First Claim: state what compiler/build factor might matter.
  - Evidence Round 1: `cd Week-01-Symptoms-Inputs-Claims/example && make debug && make release && make run-debug && make run-release`
  - Mentor Interruption: what changed and what stayed constant.
  - Evidence Round 2: inspect `Makefile` flags and identify which flags support debugging.
  - Debrief: debugging is controlled learning.
  - Apprentice Notes: concise investigation note.
  - Mentor Rubric: strong answers name symptom, build input, evidence, update, and next move.

- [ ] **Step 2: Rewrite Week 2**

  Use the canonical weekly sections:

  - Investigation: recursive Fibonacci behavior must be understood at runtime.
  - Evidence Round 1: `cd Week-02-Runtime-State/example && make && gdb ./fib`
  - Include commands: `break fib`, `run 10`, `bt`, `info args`, `info locals`, `finish`, `break fib if n == 3`.
  - Debrief: a breakpoint is a question about state.

- [ ] **Step 3: Rewrite Week 3**

  Use the canonical weekly sections:

  - Investigation: suspicious state changes before the visible failure.
  - Evidence Round 1: `cd Week-03-Causality/example && make && gdb ./watchpoint_demo`
  - Include commands: `break main`, `run`, `watch secret`, `continue`.
  - Evidence Round 2: optional `make rr` and `make replay` if `rr` is installed.
  - Debrief: causality beats source-order reading.

- [ ] **Step 4: Verify Weeks 1-3**

  Run:

  ```bash
  rg -n "^## (Investigation|Mentor Opening|First Claim|Evidence Round 1|Mentor Interruption|Evidence Round 2|Debrief|Apprentice Notes|Mentor Rubric)" Week-01-Symptoms-Inputs-Claims/README.md Week-02-Runtime-State/README.md Week-03-Causality/README.md
  git diff --check -- Week-01-Symptoms-Inputs-Claims/README.md Week-02-Runtime-State/README.md Week-03-Causality/README.md
  ```

  Expected: each file has all required sections and no whitespace errors.

- [ ] **Step 5: Commit Weeks 1-3**

  Run:

  ```bash
  git add Week-01-Symptoms-Inputs-Claims/README.md Week-02-Runtime-State/README.md Week-03-Causality/README.md
  git commit -m "Rewrite early debugging modules as mentor dialogues"
  ```

## Task 4: Weeks 4-6 Dialogue Rewrites

**Files:**
- Modify: `Week-04-Postmortem-Evidence/README.md`
- Modify: `Week-05-Ownership-Lifetime/README.md`
- Modify: `Week-06-Runtime-Checks/README.md`

- [ ] **Step 1: Rewrite Week 4**

  Use the canonical weekly sections:

  - Investigation: a crash happened outside an interactive debugger.
  - Evidence Round 1: `cd Week-04-Postmortem-Evidence/example && make && ./crash`
  - Evidence Round 2: enable core dumps where supported, then inspect with GDB.
  - Debrief: preserve postmortem evidence before changing state.

- [ ] **Step 2: Rewrite Week 5**

  Use the canonical weekly sections:

  - Investigation: memory corruption must be classified from a report.
  - Evidence Round 1: `cd Week-05-Ownership-Lifetime/example && make && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./01_heap_overflow`
  - Evidence Round 2: run the same command shape against `./04_uninitialized` or `./07_leak`.
  - Debrief: ownership and lifetime must tell one consistent story.

- [ ] **Step 3: Rewrite Week 6**

  Use the canonical weekly sections:

  - Investigation: sanitizer output points to a precise undefined behavior boundary.
  - Evidence Round 1: `cd Week-06-Runtime-Checks/example && make asan && ./asan_demo`
  - Evidence Round 2: `make ubsan && ./ubsan_demo`
  - Debrief: sanitizer reports are not root causes by themselves; they are high-quality evidence.

- [ ] **Step 4: Verify Weeks 4-6**

  Run:

  ```bash
  rg -n "^## (Investigation|Mentor Opening|First Claim|Evidence Round 1|Mentor Interruption|Evidence Round 2|Debrief|Apprentice Notes|Mentor Rubric)" Week-04-Postmortem-Evidence/README.md Week-05-Ownership-Lifetime/README.md Week-06-Runtime-Checks/README.md
  git diff --check -- Week-04-Postmortem-Evidence/README.md Week-05-Ownership-Lifetime/README.md Week-06-Runtime-Checks/README.md
  ```

  Expected: each file has all required sections and no whitespace errors.

- [ ] **Step 5: Commit Weeks 4-6**

  Run:

  ```bash
  git add Week-04-Postmortem-Evidence/README.md Week-05-Ownership-Lifetime/README.md Week-06-Runtime-Checks/README.md
  git commit -m "Rewrite memory and postmortem modules as mentor dialogues"
  ```

## Task 5: Weeks 7-10 Dialogue Rewrites

**Files:**
- Modify: `Week-07-Nondeterminism-1/README.md`
- Modify: `Week-08-Nondeterminism-2/README.md`
- Modify: `Week-09-Signals-Observability/README.md`
- Modify: `Week-10-Full-Investigation/README.md`

- [ ] **Step 1: Rewrite Week 7**

  Use the canonical weekly sections:

  - Investigation: counter output changes between runs.
  - Evidence Round 1: `cd Week-07-Nondeterminism-1/example && make && ./race_counter && ./race_counter`
  - Evidence Round 2: `make tsan && ./tsan_race`, then compare `./race_counter_mutex` and `./race_counter_atomic`.
  - Debrief: one passing concurrent run proves very little.

- [ ] **Step 2: Rewrite Week 8**

  Use the canonical weekly sections:

  - Investigation: a program appears hung.
  - Evidence Round 1: `cd Week-08-Nondeterminism-2/example && make && ./deadlock`
  - Evidence Round 2: attach with GDB or inspect threads where supported; compare `./deadlock_fixed`.
  - Debrief: live debugging should inspect before disturbing the system.

- [ ] **Step 3: Rewrite Week 9**

  Use the canonical weekly sections:

  - Investigation: the program must keep running while the learner gathers evidence.
  - Evidence Round 1: `cd Week-09-Signals-Observability/example && make && LOG_LEVEL=debug ./server`
  - Evidence Round 2: use `strace` if available, otherwise compare log levels; run `./cpu_hog` and optionally `perf`.
  - Debrief: observability answers questions without stopping the program.

- [ ] **Step 4: Rewrite Week 10**

  Use the canonical weekly sections:

  - Investigation: final capstone chosen from crash, hang, memory corruption, concurrency, or slowness.
  - Evidence Round 1: choose one previous example and run the first playbook tool.
  - Evidence Round 2: produce a postmortem claim and one prevention change.
  - Debrief: the learner must defend the investigation, not just finish it.

- [ ] **Step 5: Verify Weeks 7-10**

  Run:

  ```bash
  rg -n "^## (Investigation|Mentor Opening|First Claim|Evidence Round 1|Mentor Interruption|Evidence Round 2|Debrief|Apprentice Notes|Mentor Rubric)" Week-07-Nondeterminism-1/README.md Week-08-Nondeterminism-2/README.md Week-09-Signals-Observability/README.md Week-10-Full-Investigation/README.md
  git diff --check -- Week-07-Nondeterminism-1/README.md Week-08-Nondeterminism-2/README.md Week-09-Signals-Observability/README.md Week-10-Full-Investigation/README.md
  ```

  Expected: each file has all required sections and no whitespace errors.

- [ ] **Step 6: Commit Weeks 7-10**

  Run:

  ```bash
  git add Week-07-Nondeterminism-1/README.md Week-08-Nondeterminism-2/README.md Week-09-Signals-Observability/README.md Week-10-Full-Investigation/README.md
  git commit -m "Rewrite advanced debugging modules as mentor dialogues"
  ```

## Task 6: Repository Hygiene and Final Verification

**Files:**
- Modify: `.gitignore` if tracked binary inspection shows an ignore gap.
- Remove from Git: tracked compiled artifacts only, if present.

- [ ] **Step 1: Identify tracked compiled artifacts**

  Run:

  ```bash
  git ls-files 'Week-*/example/*' | while read -r path; do file "$path"; done
  ```

  Expected: source files and build files are preserved. Executable binaries are candidates for removal from Git.

- [ ] **Step 2: Remove tracked compiled artifacts if present**

  For each tracked compiled executable reported by `file`, run:

  ```bash
  git rm --cached <tracked-binary-path>
  ```

  Then add ignore rules to `.gitignore` for generated binaries only. Do not ignore source files, Makefiles, CMake files, scripts, or suppression files.

- [ ] **Step 3: Run final consistency checks**

  Run:

  ```bash
  rg -n "UNRESOLVED_PLACEHOLDER|FILL_ME|FIX_BEFORE_SHIPPING" README.md mentor-guide.md learner-guide.md investigation-template.md discussion-rubric.md Week-*/README.md
  rg -L "^## Investigation" Week-*/README.md
  rg -L "^## Mentor Opening" Week-*/README.md
  rg -L "^## First Claim" Week-*/README.md
  rg -L "^## Evidence Round 1" Week-*/README.md
  rg -L "^## Mentor Interruption" Week-*/README.md
  rg -L "^## Evidence Round 2" Week-*/README.md
  rg -L "^## Debrief" Week-*/README.md
  rg -L "^## Apprentice Notes" Week-*/README.md
  rg -L "^## Mentor Rubric" Week-*/README.md
  git diff --check
  ```

  Expected:

  - placeholder scan returns no unresolved curriculum placeholders
  - every `rg -L` required-section command returns no weekly README paths
  - `git diff --check` exits successfully

- [ ] **Step 4: Run representative example builds**

  Run:

  ```bash
  make -C Week-01-Symptoms-Inputs-Claims/example clean
  make -C Week-01-Symptoms-Inputs-Claims/example debug
  make -C Week-02-Runtime-State/example clean
  make -C Week-02-Runtime-State/example
  make -C Week-05-Ownership-Lifetime/example clean
  make -C Week-05-Ownership-Lifetime/example
  make -C Week-07-Nondeterminism-1/example clean
  make -C Week-07-Nondeterminism-1/example
  ```

  Expected: representative examples still build. If a command fails because a tool is unavailable, record the exact failure and continue with the remaining checks.

- [ ] **Step 5: Commit final hygiene**

  Run:

  ```bash
  git add README.md mentor-guide.md learner-guide.md investigation-template.md discussion-rubric.md Week-*/README.md .gitignore
  git commit -m "Verify debugging apprenticeship rewrite"
  ```

  If no hygiene changes remain after prior commits, skip this commit and record that the final verification had no file changes.
