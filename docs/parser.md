# Parser Module

## Overview
The parser converts raw input into an Abstract Syntax Tree (AST), where each node represents a command, operator (e.g., pipe, redirection), or argument. This tree drives execution and supports bonus features like `&&` or `||` later.

## Components
1. **Tokenization**:
   - Splits input into tokens (commands, arguments, operators) while preserving spaces inside quotes.
2. **Quote Handling**:
   - Processes single (`'`) and double (`"`) quotes for literal text or variable expansion.
3. **Variable Expansion**:
   - Replaces `$VAR` with environment values in double-quoted or unquoted contexts.
4. **AST Construction**:
   - Builds a tree with nodes for commands, pipes, redirections, and arguments.
   - Example: `echo test | cat > file` becomes a root pipe node with children for `echo test` and `cat > file`.
5. **Syntax Validation**:
   - Ensures valid structure (e.g., no dangling pipes or unclosed quotes).

## Development Phases
- **Phase 1: Basic Tokenization**  
  Split input into tokens (e.g., `echo`, `test`, `|`), ignoring quotes. Test with `echo test`.
- **Phase 2: AST Skeleton**  
  Build a simple tree for a single command (e.g., root = command, children = arguments). Test printing the tree.
- **Phase 3: Quote Handling**  
  Add quote processing to tokens, updating the tree with literal strings. Test `echo "hello world"`.
- **Phase 4: Pipes in AST**  
  Extend the AST to handle `|` as a parent node with command children. Test `echo test | cat`.
- **Phase 5: Redirections in AST**  
  Add redirection nodes (`>`, `<`) as children of commands. Test `echo test > file`.
- **Phase 6: Variable Expansion**  
  Expand variables in the tree after environment setup. Test `echo $PATH`.
- **Phase 7: Syntax Validation**  
  Validate the tree structure (e.g., no empty pipe children). Test after other modules.

## Integration Tips
- Start with a simple tree (command + args) and connect to the executor early.
- Add operator nodes (pipes, redirections) as other modules come online.
- Keep the AST flexible for bonus operators (`&&`, `||`) by using a generic node type.

## Code Ideas for Parser:

- Tokenization: Scan input char-by-char, building a token array with delimiters like spaces and |.
- AST: Define a t_node struct (type: command/pipe/redirection, value: string, children: node pointers).
- Construction: Recursively build the tree by grouping tokens under operator nodes.

---

To go back to our development process, see our [Project Approach](project_approach.md).

