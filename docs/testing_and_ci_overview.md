# Testing Strategy for Minishell

## Inital Thoughts

Since Minishell is our first team project at 42 Berlin and we’re introducing Continuous Integration (CI) and testing frameworks, here’s a practical plan to get started while keeping it beginner-friendly:

### 1. Start with Unity for Unit Testing
- **Why**: Unity is simple, lightweight, and perfect for testing individual functions in C. It aligns with 42’s hands-on approach.
- **How**: Download Unity from GitHub, include it in the project, and write tests for core functions.
- **Goal**: Test components like parsing, builtins, and variable expansion in isolation.

### 2. Add Basic Integration Tests with Scripts
- **Why**: Unity focuses on unit tests; integration tests (e.g., pipes, redirects) need a different approach. Scripts are a simple start.
- **How**: Compile Minishell, then use bash scripts to test interactions by feeding inputs and checking outputs.
- **Goal**: Verify that components like parsing and execution work together.

### 3. Introduce CI with GitHub Actions
- **Why**: Automate testing on every push to catch issues early and improve team collaboration.
- **How**: Set up a GitHub Actions workflow to build Minishell and run unit tests automatically.
- **Goal**: Ensure tests run consistently; later add integration scripts to the pipeline.

### 4. Explore Advanced Testing Tools (Later)
- **Criterion**: Upgrade to Criterion for crash detection and detailed CI reports after mastering Unity.
- **Memory Testing**: Use Valgrind to check for leaks and overflows.
- **Fuzzing**: Experiment with AFL or a custom fuzzer to test Minishell with random inputs.
- **Stress Testing**: Run large inputs or long pipelines manually or via scripts.
- **Goal**: Enhance robustness once the basics are solid.

## Timeline
- **Week 1**: Set up Unity, write 5-10 unit tests for core functions, test locally.
- **Week 2**: Add a basic CI pipeline to run unit tests on every push.
- **Week 3**: Write 2-3 integration test scripts (e.g., pipes, redirects) and integrate into CI.
- **Later**: Introduce Valgrind for memory checks and a simple fuzzer for extra credit.

## Why This Approach?
- **Unity**: Simple start for unit testing, grows our skills.
- **Scripts**: Practical for integration without overcomplicating early.
- **CI**: Team-friendly, ensures consistency.
- **Advanced Tools**: Future-proofing as we learn more.

This keeps Minishell testing manageable while introducing CI and frameworks effectively!


---

## Table of Contents
1. [Testing Strategies](#testing-strategies)  
   1. [Unit Testing](#1-unit-testing)  
   2. [Integration Testing](#2-integration-testing)  
   3. [End-to-End Testing](#3-end-to-end-testing)  
   4. [Specialized Tests (Fuzz, Memory, Stress)](#4-specialized-tests-fuzz-memory-stress)  
2. [Combined Approach: How to Implement These Tests](#combined-approach-how-to-implement-these-tests)  
3. [Continuous Integration (CI)](#continuous-integration-ci)  
   1. [Common CI Solutions](#1-common-ci-solutions)  
   2. [Best Practices](#2-best-practices)  
4. [GitHub Actions Setup](#github-actions-setup)  
   1. [Basic Concepts](#1-basic-concepts)  
   2. [Example Workflow YAML](#2-example-workflow-yaml)  
   3. [Stages of Development](#3-stages-of-development)  
5. [Summary](#summary)

---

## Testing Strategies

### 1. Unit Testing
- **Description**: Tests individual functions in isolation (e.g., `parse_line()`, `expand_variables()`).
- **Pros**: Immediate feedback, easy to pinpoint errors, helps prevent regressions.
- **Cons**: Doesn’t guarantee modules work together perfectly.
- **Example**: For `parse_line()`, feed different command strings and verify parsing outputs match expected tokens.

[Memory Tests](memory_tests.md)

### 2. Integration Testing
- **Description**: Checks how different parts of Minishell work together (e.g., parser + built-ins + environment expansions).
- **Pros**: Realistic scenarios, catches interface mismatches.
- **Cons**: More complex debugging if something breaks.
- **Example**: Pipe output of `echo $USER` into `grep`, verifying the integrated flow from variable expansion to command execution.

### 3. End-to-End Testing
- **Description**: Treat Minishell like a black box, running real commands (with piping, redirections, etc.), comparing outputs to expected results or Bash.
- **Pros**: Ensures actual user workflows behave correctly, high confidence in full system correctness.
- **Cons**: Harder to pinpoint root causes, can be slower.
- **Example**: Run a script with multiple commands (`cd`, `ls`, `echo $?`) and compare output to Bash output.

### 4. Specialized Tests (Fuzz, Memory, Stress)
- **Fuzz Testing**: Feeds random or malformed data into Minishell to uncover edge-case crashes.
- **Memory Testing**: Uses tools like Valgrind to check for leaks and invalid memory accesses.
- **Stress Testing**: Runs large or extreme workloads (very long commands, deep pipelines) to ensure performance and stability.

---

## Combined Approach: How to Implement These Tests

1. **Unit Tests First**  
   - Write tests for individual functions (e.g., parser, variable expansion).
2. **Integration Tests**  
   - After individual functions work, combine them to test entire workflows (e.g., parse + execute).
3. **End-to-End Tests**  
   - Simulate real user sessions with scripts or by piping commands to your shell.
4. **Fuzz/Memory/Stress Tests**  
   - Once the core functionality is stable, add these to find hidden crashes, leaks, or performance issues.

**Set up a folder structure like:**
```text
tests/
├── unit/
├── integration/
├── end_to_end/
└── fuzz/
```
## Continuous Integration (CI)

### 1. Common CI Solutions
- **GitHub Actions**  
  - Integrated with GitHub, large marketplace of actions, YAML-based config.  
  - Generous free tier for public repos.  
- **GitLab CI**  
  - Fully integrated with GitLab, powerful caching, easy to self-host.  
- **Jenkins**  
  - Self-hosted, very extensible, large plugin ecosystem, but heavier setup.  
- **Travis CI**  
  - Simple YAML config, used widely by open-source, free tier somewhat limited now.  
- **CircleCI**  
  - Speed-focused, parallel builds, has free plans for open-source, can get complex at advanced levels.

### 2. Best Practices
- **Keep Builds Fast**: Aim for under 10 minutes, so developers get quick feedback.  
- **Automate All Tests**: Unit, integration, end-to-end, plus linting or static analysis.  
- **Fail Fast**: Stop the process on major errors to save time.  
- **Clear Logs**: Make it obvious what went wrong and how to fix it.  
- **Manage Secrets Securely**: Store in CI’s secret manager, never in code.  
- **Use Artifacts**: Keep compiled binaries, coverage reports, or logs for debugging.

---

## GitHub Actions Setup

### 1. Basic Concepts
- **Workflows**: Instructions (in `.yml` files) that tell GitHub when and how to run your tasks.
- **Events**: Conditions that trigger workflows (like pushing code or opening a pull request).
- **Steps**: Each command or operation in the workflow (e.g., install dependencies, build code, run tests).

### 2. Example Workflow YAML

Create a file at `.github/workflows/ci.yml` in your repository:

```yaml
name: Minishell CI

on:
  push:
  pull_request:

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - name: Check out the code
        uses: actions/checkout@v2

      - name: Set up C compiler
        run: sudo apt-get update && sudo apt-get install -y build-essential

      - name: Compile project
        run: make

      - name: Run unit tests
        run: make unit-test

      - name: Run integration tests
        run: make integration-test

      - name: End-to-end tests
        run: make e2e-test
```
1. **Checkout** pulls your code from GitHub.  
2. **Install C compiler** sets up a Linux environment.  
3. **Compile** uses `make`.  
4. **Run your test targets** for unit, integration, and end-to-end tests.

### 3. Stages of Development
1. **Early Stage**: Add basic *unit tests* to ensure each function works as expected.  
2. **Middle Stage**: Write *integration tests* that confirm your modules talk to each other properly.  
3. **Late Stage**: Include *end-to-end tests* that simulate user commands (piping, redirection, environment variables, etc.).  
4. **Extra**: Add *fuzz testing*, *memory checks* (Valgrind), and *stress tests* once your shell is more robust.

---

## Summary

1. **Start Small**: Begin with unit tests, verifying each function in isolation.  
2. **Grow in Complexity**: Add integration tests, then end-to-end tests.  
3. **Use CI Early**: GitHub Actions can automatically compile and test your code for each push or pull request.  
4. **Iterate & Improve**: Over time, add specialized tests (fuzz, memory, stress) as you refine your shell and gain confidence in the basics.  
5. **Automation & Consistency**: This keeps your codebase healthy, helps catch mistakes quickly, and follows industry best practices for continuous integration.

---
To go back to our development process, see [`docs/project_approach.md`](docs/project_approach.md).
