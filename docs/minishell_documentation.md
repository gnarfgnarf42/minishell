# Minishell Overview (Macro to Micro)

This document provides a **top-down** explanation of what a shell (and by extension, a **minishell**) does. We begin at a **macro** (high-level) overview, then move step-by-step into lower levels of detail.

---

## 1. Macro (High-Level) View

### What is a Shell?

- **Definition**: A shell is a command-line interface that enables users to interact with the operating system.  
- **Core Purpose**:  
  1. **Read** commands or input from the user.  
  2. **Interpret** or parse that input to understand what needs to be done.  
  3. **Execute** tasks by launching programs or built-in functionalities.  
  4. **Provide Feedback** (such as errors, output) to the user.

### What is a Minishell?

- **Minishell** is a simplified reimplementation of a standard Unix shell (like `bash` or `zsh`).  
- **Goal**: Demonstrate the essential mechanics of a shell in a more approachable project scope.  
- **Key Features** (at a high level):  
  - Displays a prompt and waits for user commands.  
  - Interprets typical shell syntax (quotes, environment variables, redirections, etc.).  
  - Executes programs or built-in commands.  
  - Manages processes (forking, piping, redirection).

At the **macro level**, both a full shell and a minishell revolve around **reading** user input, **interpreting** that input, and **running** commands in a structured environment.

---

## 2. Meso (Intermediate) View

Here we start to break down the shell’s components. While still focusing on a fairly broad perspective, we show **how** the shell is organized internally.

### 2.1 Main Components

1. **Input/Prompt**  
   - Prints a prompt (like `minishell> `) and reads user input.  
   - In a real shell, often done using a library like `readline`.  

2. **Parser**  
   - Splits user input into smaller pieces (tokens).  
   - Interprets quotes, environment variable expansions, redirections, etc.  
   - Structures the tokens into executable commands or pipelines.  

3. **Executor**  
   - Takes the parsed commands and **executes** them.  
   - For external commands (e.g. `/bin/ls`), it locates the binary and uses `fork()` + `execve()`.  
   - For built-in commands (e.g. `cd`, `echo`), it calls internal functions directly.  
   - Manages **redirections** (`>`, `<`) and **pipes** (`|`).  

4. **Environment Manager**  
   - Stores and retrieves environment variables (e.g. `PATH`, `HOME`).  
   - Updates environment data when the user calls built-in commands like `export` or `unset`.

5. **Error & Signal Handling**  
   - Displays meaningful error messages (e.g. “command not found”).  
   - Reacts to signals like **Ctrl-C** (interrupt) and **Ctrl-\\** (quit).  

### 2.2 Typical Data Flow

1. **User Input**  
   The user types a command line at the prompt, e.g. `cat file | grep foo > output.txt`.
2. **Parsing**  
   The minishell tokenizes the input into segments: `["cat", "file", "|", "grep", "foo", ">", "output.txt"]`.  
3. **Command Construction**  
   The parser identifies that `cat file` pipes to `grep foo`, whose output is redirected to `output.txt`.
4. **Execution**  
   - Minishell creates a pipeline:  
     - First process: `cat file`  
     - Second process: `grep foo`  
   - Applies redirection so the second process’s output goes to the file `output.txt`.
5. **Feedback**  
   - If successful, minishell eventually returns to the prompt.  
   - If an error arises (e.g. `file` doesn’t exist), it displays an error message.

---

## 3. Micro (Detailed) View

Now we look at the **lower-level** details, explaining the typical internal sub-systems and how they might be implemented in code.

### 3.1 Main Loop

1. **Initialization**  
   - Set up signals (so Ctrl-C doesn’t kill the shell but returns to a prompt).  
   - Possibly load or initialize shell-specific environment data.  
2. **Loop**  
   - **Display Prompt**  
   - **Read Input** (via `readline` or equivalent).  
   - **Parse Input** into a structure describing commands, arguments, redirections.  
   - **Execute** the parsed command(s).  
   - **Cleanup** resources after execution.  
   - Repeat until an `exit` command or end-of-file (Ctrl-D).

### 3.2 Parsing Details

1. **Lexical Analysis**  
   - Breaks the input string by whitespace and recognizes special symbols (`|`, `<`, `>`, `<<`, `>>`).  
   - Handles quotes (e.g. `"some text"` or `'literal'`).  
   - Expands environment variables (`$VAR`) into their values.  

2. **Syntactic Analysis**  
   - Uses tokens from the lexer to form command structures.  
   - Identifies sequences of commands separated by `|` (pipes).  
   - Identifies input/output redirections, storing which file or “delimiter” to use.  

3. **Command/AST (Abstract Syntax Tree)**  
   - Many shells use an internal tree or linked list representation. E.g. a pipeline of commands is a list, each node containing:  
     - Command name  
     - Arguments  
     - Redirection info  

### 3.3 Execution Details

1. **Built-Ins vs External Commands**  
   - **Built-ins** (`cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`): Run in the same process; no need to `fork` unless piping demands it.  
   - **External commands**:  
     - Use `fork()` to create a child process.  
     - Inside the child, use `execve()` to replace the child’s image with the new program.  
     - Parent process may wait for the child to complete.  

2. **Redirection**  
   - For `> file`, open `file` for writing and replace `STDOUT_FILENO` with that file descriptor.  
   - For `< file`, open `file` for reading and replace `STDIN_FILENO`.  
   - For `>> file`, open `file` in **append** mode.  
   - For `<< EOF` (heredoc), read until encountering the delimiter (`EOF`), store into a temporary file or buffer, and then treat it as `<` from that source.

3. **Pipes**  
   - A pipe has two ends: **reading** (`pipefd[0]`) and **writing** (`pipefd[1]`).  
   - When executing `cmd1 | cmd2`, `cmd1`’s **stdout** is redirected to the pipe’s **writing** end, and `cmd2`’s **stdin** is connected to the pipe’s **reading** end.

### 3.4 Environment Management

- **Storage**: Often stored as a linked list or array of `char *` strings like `KEY=VALUE`.  
- **Lookup**: When a command references `$HOME`, the shell looks up `HOME` in the environment array.  
- **Modification**: Built-in commands (`export`, `unset`) add, change, or remove entries.

### 3.5 Error & Signal Handling

1. **Errors**  
   - Common errors: “command not found,” “no such file or directory,” “permission denied.”  
   - The shell typically sets an **exit status** variable (`$?`) to an integer code.  
2. **Signals**  
   - **SIGINT** (Ctrl-C): Usually interrupts the current command and brings you back to a prompt.  
   - **SIGQUIT** (Ctrl-\): May quit the current running program.  
   - The shell has custom handlers for these signals to avoid terminating outright.

---

## Putting It All Together

- **Macro Level**: Minishell provides an interface for entering commands, interpreting them, and running them—exactly what “shell” implies.  
- **Meso Level**: Internally, minishell is divided into parts—Input, Parsing, Execution, Environment, etc.—to keep it organized and maintainable.  
- **Micro Level**: Each part has its own logic, from splitting lines into tokens to managing file descriptors for redirections and pipes.

A **minishell** is, therefore, a **scaled-down** version of a fully-fledged shell, but still includes all the fundamental steps: **Prompt → Parse → Execute → Feedback**.

---

## Conclusion

By examining **minishell** from macro to micro levels, we see **how** a shell operates at each stage:

1. **Macro**: Shell = read + interpret + execute + feedback.  
2. **Meso**: Organized into logical modules: parser, executor, environment, etc.  
3. **Micro**: Detailed functions, system calls (`fork`, `execve`, `dup2`, etc.), and data structures that handle user commands seamlessly.

This hierarchy helps clarify both the overall vision (a shell that can interpret and run commands) and the individual nuts-and-bolts (data structures, system calls, error handling) that make a shell function correctly.

# Additional Considerations

## Overview
These ensure a robust Minishell with an AST, meeting 42 requirements and supporting team collaboration.

## Components
1. **Memory Management**:
   - Frees the AST and all allocations.
2. **Error Handling**:
   - Reports parsing or execution errors clearly.
3. **Single Global Variable**:
   - Limits globals (e.g., exit status).
4. **Readline Library**:
   - Enhances input with history.
5. **Bonus Readiness**:
   - Prepares the AST for `&&`, `||`, or parentheses.

## Development Phases
- **Phase 1: AST Memory**  
  Free tree nodes recursively. Test with simple commands.
- **Phase 2: Error Messages**  
  Add errors for parsing/execution. Test after each module.
- **Phase 3: Readline**  
  Integrate `readline` after the main loop works.
- **Phase 4: Bonus Prep**  
  Design the AST with node types for `&&`, `||` (implement later).
- **Phase 5: Team Workflow**  
  Use Git and assign tasks (e.g., parser vs. executor).

## Integration Tips
- Free the AST after each command execution to avoid leaks.
- Pass data via pointers to avoid globals.
- Test with valgrind to catch memory issues.

## Development Timeline

Week 1: Main loop + Parser (tokenization + basic AST) + Builtins (echo, pwd).
Week 2: Executable (single command from AST) + Signals (Ctrl+C, Ctrl+D).
Week 3: Parser (quotes + pipe nodes) + Pipes (single pipe).
Week 4: Parser (redirection nodes) + Redirections (output, input).
Week 5: Builtins (cd, env, exit) + Pipes (multiple).
Week 6: Parser (variables) + Redirections (append, here-doc).
Week 7: Builtins (export, unset) + Error Handling + AST Cleanup.
Week 8: Polish (readline, memory) + Bonus Prep (design for &&, ||).

This timeline prioritizes the AST in the parser, building a solid foundation for execution, then layering features. It keeps the bonus in mind without committing to it early. 

---

To go to the development process, see our [Project Approach](project_approach.md).


# Minishell – Allowed Library Functions Overview

Below is an **overview** of all **allowed library functions** for the Minishell project, as stated in the project PDF, along with **brief descriptions** of what each function does or is commonly used for in a shell context.

| **Function**           | **Description**                                                                                                                                                                         |
|------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **readline**           | Reads a line from the terminal with editing capabilities (e.g. arrow keys).                                                                                                            |
| **rl_clear_history**   | Clears the in-memory readline history.                                                                                                                                                 |
| **rl_on_new_line**     | Notifies readline that the cursor has moved to a new line (often used after signals).                                                                                                  |
| **rl_replace_line**    | Replaces the current input line with a new line buffer.                                                                                                                                |
| **rl_redisplay**       | Redisplays the current input line (useful when signal-handling to refresh the prompt).                                                                                                 |
| **add_history**        | Adds a string to the readline history.                                                                                                                                                 |
| **printf**             | Formats and prints output to stdout (a more flexible version of `print`).                                                                                                              |
| **malloc**             | Allocates memory on the heap.                                                                                                                                                          |
| **free**               | Frees previously allocated memory.                                                                                                                                                     |
| **write**              | Writes bytes to a file descriptor (e.g. `STDOUT_FILENO`).                                                                                                                              |
| **access**             | Checks a file’s accessibility (existence, permissions, etc.).                                                                                                                          |
| **open**               | Opens a file and returns a file descriptor (used for redirections, etc.).                                                                                                              |
| **read**               | Reads bytes from a file descriptor.                                                                                                                                                    |
| **close**              | Closes a file descriptor.                                                                                                                                                              |
| **fork**               | Creates a new process (child) by duplicating the calling process (parent).                                                                                                             |
| **wait** / **waitpid** | Waits for a child process to change state (exit, stop, etc.).                                                                                                                          |
| **wait3** / **wait4**  | Variants of `wait` that can provide additional resource-usage info (e.g., CPU time) or handle multiple children.                                                                       |
| **signal**             | Simple API to set a handler for a specific signal (e.g., `SIGINT`).                                                                                                                    |
| **sigaction**          | More advanced API to set signal handlers with additional options.                                                                                                                      |
| **sigemptyset**        | Initializes a signal set to exclude all signals.                                                                                                                                       |
| **sigaddset**          | Adds a signal to a signal set.                                                                                                                                                         |
| **kill**               | Sends a signal to a process or group of processes.                                                                                                                                     |
| **exit**               | Terminates the calling process with a specified exit status.                                                                                                                           |
| **getcwd**             | Retrieves the current working directory.                                                                                                                                               |
| **chdir**              | Changes the current working directory.                                                                                                                                                 |
| **stat** / **lstat** / **fstat** | Retrieves information (e.g., size, permissions) about a file. `stat` operates on a path, `lstat` also works with symbolic links, and `fstat` uses a file descriptor.                    |
| **unlink**             | Removes a file name from the filesystem (often used for removing temporary files).                                                                                                     |
| **execve**             | Replaces the current process image with a new program (executable).                                                                                                                    |
| **dup** / **dup2**     | Duplicates a file descriptor, often used for redirections (e.g., `dup2(fd, STDOUT_FILENO)`).                                                                                           |
| **pipe**               | Creates a unidirectional communication channel (read-end, write-end).                                                                                                                  |
| **opendir** / **readdir** / **closedir** | Used for directory handling. `opendir` returns a directory stream, `readdir` iterates entries, and `closedir` closes the stream.                                                   |
| **strerror**           | Returns a string describing an error code (typically from `errno`).                                                                                                                    |
| **perror**             | Prints an error message to `stderr` based on the current `errno`.                                                                                                                      |
| **isatty**             | Tests if a file descriptor refers to a terminal device.                                                                                                                                |
| **ttyname**            | Returns the name of the terminal device associated with a file descriptor.                                                                                                             |
| **ttyslot**            | Finds the slot number of the current user in the utmp file (often not used frequently, but is allowed).                                                                                |
| **ioctl**              | System call to control device parameters (terminals, etc.).                                                                                                                            |
| **getenv**             | Retrieves the value of an environment variable.                                                                                                                                        |
| **tcsetattr** / **tcgetattr** | Gets or sets terminal attributes (e.g. disabling echo, canonical mode).                                                                                                                      |
| **tgetent** / **tgetflag** / **tgetnum** / **tgetstr** / **tgoto** / **tputs** | Terminal handling functions from the termcap library (e.g., for capability lookups, cursor movements, etc.).                                              |

> **Note**:  
> - Some of these functions (like `readline` and its related `rl_...` functions) may come from additional libraries (e.g., `-lreadline`).  
> - The `tc...` and `tget...` functions handle low-level terminal capabilities, often used for advanced line-editing or terminal behavior.  
> - Not all functions are necessarily required to implement a basic minishell, but **they are allowed** if you need them.

This completes the list of **allowed** external functions for the project. Refer to each function’s **man page** or library documentation for deeper usage details. 

---

To go back to our development process, see our [Project Approach](project_approach.md).

