# Pipes Module

## Overview
Pipes connect commands in the AST, where `|` nodes have child commands whose output and input are linked via pipe file descriptors.

## Components
1. **Pipe Creation**:
   - Creates a pipe for each `|` node.
2. **Tree Traversal**:
   - Executes left and right children of a pipe node.
3. **Redirection**:
   - Links stdout of one command to stdin of the next.
4. **Process Management**:
   - Forks and waits for all commands in the pipeline.

## Development Phases
- **Phase 1: Single Pipe**  
  Handle one `|` node, connecting two commands. Test `echo test | cat`.
- **Phase 2: Multiple Pipes**  
  Recursively process multiple `|` nodes. Test `echo test | cat | wc`.
- **Phase 3: Pipe with Redirections**  
  Combine with redirection nodes. Test `cat file | grep test > out`.
- **Phase 4: Error Handling**  
  Check for pipe failures after other modules are stable.

## Integration Tips
- Build after the executor and parser handle single commands and pipe nodes.
- Use recursive tree traversal to execute pipelines.
- Test incrementally to isolate pipe-related bugs.

## Code Ideas for Pipes:

- Pipe: For a | node, create a pipe, fork twice, redirect stdout of the left child to the pipe write end, and stdin of the right child to the read end.
- Multi-Pipe: Recurse through | nodes, chaining pipes in a loop.

---

To go back to our development process, see our [Project Approach](project_approach.md).

