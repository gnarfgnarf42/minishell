# Redirections Module

## Overview
Redirections manage I/O by interpreting redirection nodes in the AST (`>`, `<`, `>>`, `<<`) and adjusting file descriptors for commands.

## Components
1. **Output Redirection (`>`)**:
   - Redirects stdout to a file, overwriting it.
2. **Append Redirection (`>>`)**:
   - Appends stdout to a file.
3. **Input Redirection (`<`)**:
   - Redirects stdin from a file.
4. **Here-Documents (`<<`)**:
   - Reads input until a delimiter, redirected to stdin.
5. **File Descriptor Management**:
   - Uses `dup2` to connect files to stdin/stdout.

## Development Phases
- **Phase 1: Output Redirection (`>`)**  
  Handle `>` nodes in the AST, redirecting a command’s output. Test `echo test > file`.
- **Phase 2: Append Redirection (`>>`)**  
  Extend to `>>` nodes. Test `echo more >> file`.
- **Phase 3: Input Redirection (`<`)**  
  Add `<` nodes for input. Test `cat < file`.
- **Phase 4: Here-Documents (`<<`)**  
  Implement `<<` as a node with a delimiter, using a pipe. Test after pipes work.
- **Phase 5: Multi-Redirection**  
  Handle multiple redirections per command (e.g., `< in > out`). Test later.

## Integration Tips
- Add after the executor can run commands, using AST redirection nodes.
- Traverse the tree to apply all redirections before executing a command.
- Test with pipes later for combined cases (e.g., `< file | grep test`).

## Code Ideas for Redirections:

- Redirection: For a > node, open the file and use dup2 to redirect stdout before execve.
- Here-Doc: Create a pipe, read input until the delimiter, write to the pipe, and redirect stdin.

---

To go back to our development process, see our [Project Approach](project_approach.md).
