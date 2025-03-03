# Project Approach

This document outlines **how** we’re building Minishell in a structured, iterative manner, reflecting modern industry practices.

---

## 1. Development Methodology

### 1.1 Iterative Sprints
- We break down the project into small, manageable sprints (1–2 weeks each).
- Each sprint focuses on a specific milestone (e.g., **Shell Loop**, **Parser**, **Execution Engine**, **Built-ins**, **Redirections**, **Pipes**, **Signals**, etc.).
- At the end of each sprint, we aim to have a **working** slice of Minishell (even if some features are still missing).

### 1.2 Branching Strategy
- **main branch**: Always stable, contains production-ready code.
- **dev branch**: Central integration branch where new features are merged after passing tests and reviews.
- **feature branches**: Each new feature or fix is developed on its own branch (e.g., `feature/parser`, `feature/redirections`) to avoid conflicts.
- **Pull Requests**: When a feature is ready, a PR is opened to merge into `dev`. Another team member reviews and, if everything is solid, merges.

---

## 2. Core Roadmap

We’re following a **“Core First, Then Expand”** roadmap but with industry best practices:

1. **Shell Loop & Basic Input**  
   - Display a prompt, read user input, and exit on EOF (Ctrl+D).
2. **[Modular Parser](parser.md)**  
   - Split command strings into tokens, handle quotes, manage environment expansions.
3. **[Basic Execution Engine](execution_engine.md)**  
   - Resolve executables (via `PATH` or absolute path) and run them with `fork` + `execve`.
4. **[Built-ins](builtins.md)**  
   - Implement `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`.
5. **[Redirections](redirections_module.md)**  
   - Add `<`, `>`, `<<`, `>>`.
6. **[Pipes](pipes.md)**  
   - Handle multiple commands connected by `|`.
7. **[Signals](signals.md) & Final Touches**  
   - Respond to `Ctrl-C`, `Ctrl-\`, etc. Polish code, ensure no memory leaks.
8. **(Optional) Bonuses**  
   - Logical operators (`&&`, `||`), wildcards (`*`), etc.

---

## 3. Testing & Continuous Integration

1. **Automated Tests**  
   - Each roadmap step has corresponding tests. For example:
     - Shell loop tests (prompt detection, exit on EOF).
     - Parser tests (quotes, environment variables, tricky edge cases).
     - Execution tests (both built-ins and external commands).
   - We maintain a set of test scripts or a small C-based test suite.
2. **CI Pipeline**  
   - We integrate with GitHub Actions (or another CI service) to automatically:
     - **Build** the code.
     - **Run** tests on each commit or pull request.
     - **Check** for memory leaks (using Valgrind or equivalent) when possible.

If CI finds a broken test or memory leak, we fix it before merging into `dev`.
[Click for the detailed version.](testing_and_ci_overview.md)

---

## 4. Modular & Extensible Architecture

- **Parser**: Self-contained module for tokenizing input and building an internal command structure.
- **Executor**: Consumes the parser’s output to run commands, handle redirections/pipes, and manage built-ins.
- **Built-ins**: Kept in separate functions or files (e.g., `builtins/echo.c`) for clarity and easy updates.
- **Signals**: Handled in a dedicated area to keep global state minimal (as required by the project).

This separation of concerns means we can add or refine features (like a bonus) without breaking the entire codebase.

---

## 5. Collaboration & Communication

- **Daily Stand-Ups** (or quick sync): We briefly discuss what each person is working on, any blockers, and next steps.
- **Pull Request Reviews**: Every change is peer-reviewed to maintain code quality, share knowledge, and catch errors early.
- **Project Board** (GitHub Kanban): We track to-do’s, in-progress tasks, and done items for each milestone.

---

## 6. Future Improvements

- **Refactoring**: As we learn more about shell logic, we may refine certain modules (e.g., optimizing the parser or reorganizing built-ins).
- **More Tests**: We plan to expand our test suite with tricky cases (nested quotes, multiple environment variables, etc.).
- **Performance Checks**: While Minishell isn’t about pure performance, we’ll keep an eye out for any glaring inefficiencies.

---

## 7. Conclusion

By combining a straightforward roadmap (“Core First, Then Expand”) with **feature branching, automated testing, CI integration, and a modular design**, we aim to:

- Deliver reliable, incremental progress.
- Ensure code quality through peer reviews and continuous testing.
- Remain flexible for advanced bonus features.

We hope this transparent approach not only helps us succeed with Minishell but also reflects modern professional software development practices.

