# Signals Module

## Overview
Signals manage interrupts (Ctrl+C, Ctrl+D) by catching them and adjusting shell behavior, working with the AST-driven execution flow.

## Components
1. **SIGINT (Ctrl+C)**:
   - Stops the current command and resets the prompt.
2. **SIGQUIT (Ctrl+\)**:
   - Often ignored in Minishell.
3. **EOF (Ctrl+D)**:
   - Exits if input is empty.
4. **Signal Handlers**:
   - Custom functions for signal behavior.

## Development Phases
- **Phase 1: Ctrl+C**  
  Catch SIGINT to reset the prompt. Test with a running command.
- **Phase 2: Ctrl+D**  
  Exit on EOF in the input loop. Test with empty input.
- **Phase 3: Child Signals**  
  Ensure child processes from the AST execution handle signals. Test after pipes.
- **Phase 4: SIGQUIT (Optional)**  
  Ignore or handle Ctrl+\ if needed. Test later.

## Integration Tips
- Add early to manage interrupts during testing.
- Adjust handlers to work with AST execution (e.g., killing child processes).
- Keep handlers minimal to avoid complexity.

## Code Ideas for Signals:

- SIGINT: Set signal(SIGINT, handler) to print a newline and redisplay the prompt.
- Child Signals: Ignore SIGINT in the parent, let children inherit default behavior.
---

To go back to our development process, see our [Project Approach](project_approach.md).
