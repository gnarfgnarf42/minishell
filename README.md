# Minishell Project

Welcome to our **Minishell** project! This is a simplified shell built as part of the 42 curriculum. Our goal is to replicate core shell functionalities (prompt, command parsing, built-ins, pipes, redirections, and more) while maintaining robust code quality and an iterative, professional workflow.

---

## Project Overview

- **Subject**: Rebuild a miniature version of a UNIX shell
- **Key Features**:
  - Display a prompt and read user input
  - Parse commands (including quotes and environment variables)
  - Execute commands via `fork` and `execve`
  - Implement built-in commands (e.g., `cd`, `echo`, `env`, `exit`, etc.)
  - Handle redirections and pipes
  - Manage signals like `Ctrl-C`, `Ctrl-\`, `Ctrl-D`
- **Language**: C
- **Norm**: Compliant with 42’s Norm rules

For a detailed description of our development process, see [`docs/project_approach.md`](docs/project_approach.md).

---

## Quick Start

1. **Clone** this repository:
   ```bash
   git clone https://github.com/yourname/minishell.git
   cd minishell
2. **Build** the project (using the provided Makefile):
   ```bash
   make
3. **Run** Minishell:
   ```bash
   ./minishell
4. **Test**
   ```bash
   ./run_tests.sh
