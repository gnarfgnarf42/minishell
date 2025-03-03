# Builtins Module

## Overview
Builtins are shell-internal commands executed without forking, implemented by checking the AST’s command nodes and running custom logic.

## Components
1. **Echo**:
   - Prints arguments, supporting `-n`.
2. **Cd**:
   - Changes directory, updating `$PWD` and `$OLDPWD`.
3. **Pwd**:
   - Prints the current directory.
4. **Export**:
   - Sets environment variables.
5. **Unset**:
   - Removes variables.
6. **Env**:
   - Lists environment variables.
7. **Exit**:
   - Exits the shell.
8. **Environment Management**:
   - Maintains a key-value store for variables.

## Development Phases
- **Phase 1: Echo and Pwd**  
  Check AST command nodes for `echo` or `pwd` and run them. Test `echo hi` and `pwd`.
- **Phase 2: Environment Setup**  
  Store `envp` in a structure for access. Test `env`.
- **Phase 3: Cd and Exit**  
  Add `cd` and `exit` logic from AST nodes. Test navigation and termination.
- **Phase 4: Export and Unset**  
  Modify the environment based on AST args. Test `export VAR=val` and `unset VAR`.

## Integration Tips
- Build early to handle basic commands before external execution.
- Check the AST’s root command node to decide builtin vs. external.
- Share the environment with the parser for variable expansion.

## Code Ideas for Builtins:

- Echo: If node value is echo, print its children (arguments), checking for -n.
- Environment: Use a linked list or array to store key=value pairs from envp.

---
To go back to our development process, see our [Project Approach](project_approach.md).
