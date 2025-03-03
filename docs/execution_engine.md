# Executable Module

## Overview
The executable module runs external commands by traversing the AST and using `fork` and `execve`. It interprets command nodes and their arguments from the tree.

## Components
1. **Tree Traversal**:
   - Walks the AST to find command nodes and their arguments.
2. **Path Resolution**:
   - Resolves command paths using `$PATH` (e.g., `ls` → `/bin/ls`).
3. **Process Creation**:
   - Forks a child process for each command execution.
4. **Command Execution**:
   - Executes the command with `execve` using tree-provided data.
5. **Error Handling**:
   - Manages “command not found” or permission errors.

## Development Phases
- **Phase 1: Simple Command Execution**  
  Execute a single command node (e.g., `echo test`) from the AST. Test with hardcoded paths.
- **Phase 2: Path Resolution**  
  Add `$PATH` lookup for command nodes. Test `echo` and `ls`.
- **Phase 3: Argument Handling**  
  Pass all child arguments from the command node to `execve`. Test `ls -l`.
- **Phase 4: Error Handling**  
  Add error checks after pipes and redirections are integrated.

## Integration Tips
- Build after the parser creates a basic AST with command nodes.
- Start with single commands, then adapt for pipes/redirections by adjusting tree traversal.
- Use a recursive function to process the tree later for complex cases.

## Code Ideas for Executable:

- Traversal: Write a execute_node function that checks if a node is a command, then forks and runs it.
- Path: Split $PATH and test each prefix with access() to find the executable.
---
To go back to our development process, see our [Project Approach](project_approach.md).
