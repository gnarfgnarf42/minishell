# Minishell Tokenizer Documentation

## Overview (TL;DR)

The tokenizer is the first step in processing user input for Minishell, turning a raw command string into a linked list of `t_token` structs. Each token has a `type` (e.g., `TOKEN_WORD`, `TOKEN_PIPE`) and a `value` (e.g., `"echo"`, `"|"`). It’s designed to handle commands, arguments, operators, and quotes, breaking them into manageable pieces for the parser.

**Example**:  
> Input: `echo "hello world" | cat`  
> Output: Tokens `[WORD: "echo"] -> [WORD: "hello world"] -> [PIPE: "|"] -> [WORD: "cat"] -> [END: ""]`

- **Where It Lives**: `src/parser/tokenizer/`
- **Key Function**: [`ft_tokenize`](#ft_tokenize) orchestrates the process.
- **Helpers**:  
  - [`ft_tokenize_loop`](#ft_tokenize_loop) runs the main loop.  
  - [`ft_process_char`](#ft_process_char) decides what each character means.  
  - [`ft_skip_whitespace`](#ft_skip_whitespace) skips spaces.  
  - [`ft_handle_operator`](#ft_handle_operator) processes `|`, `<`, `>`.  
  - [`ft_handle_quotes`](#ft_handle_quotes) handles `"..."` and `'...'`.  
  - [`ft_handle_word`](#ft_handle_word) grabs unquoted words.  
  - [`ft_create_token`](#ft_create_token) builds each token.  
  - [`ft_add_token`](#ft_add_token) links tokens together.  
  - [`ft_finalize_tokens`](#ft_finalize_tokens) adds the end marker.  
  - [`ft_free_tokens`](#ft_free_tokens) cleans up on failure.

It’s modular, norm-compliant (under 25 lines per function), and uses `ft_` prefixes for clarity.

---

## Flowchart: Tokenizing `echo "hello world" | cat`

Here’s a Markdown-friendly "flowchart" showing how the tokenizer processes `echo "hello world" | cat`. Each step links to the relevant function and includes a brief explanation.

```
START: Input = "echo \"hello world\" | cat"
  |
  v
[ft_tokenize] ----> Initialize head = NULL, i = 0
  |                   "Start the process, hand off to the loop."
  v
[ft_tokenize_loop] -> while (input[i]) { Process each char }
  |                   "Loop through the string, building tokens."
  |                   i = 0, at 'e'
  v
[ft_process_char] --> [ft_skip_whitespace] -> No whitespace, proceed
  |                   "Check for spaces; none here."
  v
[ft_process_char] --> [ft_handle_word] -> Create token: [WORD: "echo"]
  |                   "Grab 'echo' until space, i moves to 5."
  v
[ft_add_token] -----> Add [WORD: "echo"] to list
  |                   "Link first token: head = tail = echo."
  |                   i = 5, at ' '
  v
[ft_process_char] --> [ft_skip_whitespace] -> Skip space, i = 6
  |                   "Move past space to '\"'."
  v
[ft_process_char] --> [ft_handle_quotes] -> Create token: [WORD: "hello world"]
  |                   "Extract quoted string, i moves to 18."
  v
[ft_add_token] -----> Add [WORD: "hello world"] to list
  |                   "Link second token: tail->next = hello world."
  |                   i = 18, at ' '
  v
[ft_process_char] --> [ft_skip_whitespace] -> Skip space, i = 19
  |                   "Move past space to '|'."
  v
[ft_process_char] --> [ft_handle_operator] -> Create token: [PIPE: "|"]
  |                   "Identify pipe, i moves to 20."
  v
[ft_add_token] -----> Add [PIPE: "|"] to list
  |                   "Link third token."
  |                   i = 20, at ' '
  v
[ft_process_char] --> [ft_skip_whitespace] -> Skip space, i = 21
  |                   "Move past space to 'c'."
  v
[ft_process_char] --> [ft_handle_word] -> Create token: [WORD: "cat"]
  |                   "Grab 'cat' until end, i moves to 24."
  v
[ft_add_token] -----> Add [WORD: "cat"] to list
  |                   "Link fourth token."
  |                   i = 24, at '\0'
  v
[ft_tokenize_loop] -> Loop ends (input[i] == '\0')
  |
  v
[ft_finalize_tokens] -> Add [END: ""] to list
  |                   "Append end marker, return head."
  v
END: Return token list
```

**Resulting List**:  
`[WORD: "echo"] -> [WORD: "hello world"] -> [PIPE: "|"] -> [WORD: "cat"] -> [END: ""]`

---

## Detailed Function Explanations (Following the Example Flow)

Below is a comprehensive explanation of each function involved in tokenizing `echo "hello world" | cat`.This walks through the entire process in detail, step-by-step, as it happens.

### ft_tokenize
- **Purpose**: Acts as the top-level coordinator for tokenizing the input string into a linked list of `t_token` structs.
- **Variables**:
  - `t_shell *shell`: The shell context, used for memory tracking (e.g., `ft_track_malloc`, `ft_track_free`).
  - `const char *input`: The raw input string, `"echo \"hello world\" | cat"`, a null-terminated C string.
  - `t_token *head`: The pointer to the start of the token list, initialized to `NULL`.
  - `size_t i`: The index into `input`, starting at `0`.
- **Process**:
  - Initializes `head` to `NULL`, indicating an empty token list, and `i` to `0`, pointing to the first character (`'e'`).
  - Calls `ft_tokenize_loop(shell, input, &i)` to process the string and build the token list, passing the address of `i` so it can be updated.
  - After the loop, checks the result: if `head` is `NULL` and `input[i]` is not `\0`, an error (like an unclosed quote) occurred, so it returns `NULL`.
  - If successful, calls `ft_finalize_tokens(shell, head)` to append a `TOKEN_END` token and returns the completed `head`.
- **In the Example**: 
  - Starts with `shell` (memory context), `input = "echo \"hello world\" | cat"`, `head = NULL`, `i = 0`.
  - Hands off to `ft_tokenize_loop`, which returns `head` pointing to `[WORD: "echo"] -> ... -> [WORD: "cat"]`.
  - Finalizes with `ft_finalize_tokens`, returning `[WORD: "echo"] -> ... -> [END: ""]`.

### ft_tokenize_loop
- **Purpose**: Manages the main iteration over the input string, building the token list character by character.
- **Variables**:
  - `t_shell *shell`: The shell context for memory operations.
  - `const char *input`: The input string, `"echo \"hello world\" | cat"`.
  - `size_t *i`: Pointer to the current index, starting at `0`.
  - `t_token *head`: The list’s head, initially `NULL`.
  - `t_token *tail`: The list’s tail, initially `NULL`, used to append new tokens.
  - `t_token *new_token`: Temporary pointer for each new token created.
- **Process**:
  - Initializes `head` and `tail` to `NULL` (empty list).
  - Enters a `while (input[*i])` loop, checking if the current character exists (not `\0`).
  - For each iteration:
    - Calls `ft_process_char(shell, input, i)` to analyze the current character and create a `new_token`.
    - If `new_token` is `NULL` and `input[*i]` is still not `\0`, an error occurred (e.g., unclosed quote), so it calls `ft_free_tokens(shell, &head)` to clean up and returns `NULL`.
    - If `new_token` exists, calls `ft_add_token(&head, &tail, new_token)` to link it into the list.
    - If `new_token` is `NULL` and `input[*i]` is `\0`, the end is reached, so it breaks the loop.
  - Returns `head` to `ft_tokenize`.
- **In the Example**: 
  - Starts with `head = NULL`, `tail = NULL`, `*i = 0`.
  - Loops:
    - `*i = 0` (`e`): Creates `[WORD: "echo"]`, adds it, `*i = 5`.
    - `*i = 5` (space): Skips to `*i = 6`.
    - `*i = 6` (`"`): Creates `[WORD: "hello world"]`, adds it, `*i = 18`.
    - `*i = 18` (space): Skips to `*i = 19`.
    - `*i = 19` (`|`): Creates `[PIPE: "|"]`, adds it, `*i = 20`.
    - `*i = 20` (space): Skips to `*i = 21`.
    - `*i = 21` (`c`): Creates `[WORD: "cat"]`, adds it, `*i = 24`.
    - `*i = 24` (`\0`): Breaks, returns `head`.

### ft_process_char
- **Purpose**: Analyzes the current character and delegates to the appropriate handler to create a token.
- **Variables**:
  - `t_shell *shell`: Shell context for memory tracking.
  - `const char *input`: The input string.
  - `size_t *i`: Pointer to the current index.
- **Process**:
  - Calls `ft_skip_whitespace(input, i)` to move `*i` past any leading spaces.
  - Checks if `input[*i]` is `\0`; if so, returns `NULL` to signal the end.
  - Examines `input[*i]`:
    - If it’s `|` or `<` or `>`, calls `ft_handle_operator(shell, input, i)`.
    - If it’s `"` or `'`, calls `ft_handle_quotes(shell, input, i)`.
    - Otherwise, calls `ft_handle_word(shell, input, i)`.
  - Returns the resulting `t_token *` from the handler, or `NULL` if no token is needed (e.g., end of string).
- **In the Example**:
  - `*i = 0` (`e`): No whitespace, calls `ft_handle_word`, returns `[WORD: "echo"]`.
  - `*i = 5` (space): Skips to `*i = 6`, then calls `ft_handle_quotes` for `"`, returns `[WORD: "hello world"]`.
  - `*i = 18` (space): Skips to `*i = 19`, calls `ft_handle_operator` for `|`, returns `[PIPE: "|"]`.
  - `*i = 20` (space): Skips to `*i = 21`, calls `ft_handle_word` for `c`, returns `[WORD: "cat"]`.
  - `*i = 24` (`\0`): Returns `NULL`, ending the loop.

### ft_skip_whitespace
- **Purpose**: Advances the index past any whitespace characters (spaces, tabs, etc.).
- **Variables**:
  - `const char *input`: The input string.
  - `size_t *i`: Pointer to the current index.
- **Process**:
  - Uses a helper `ft_is_whitespace` to check if `input[*i]` is a whitespace character (space, tab, newline, etc.).
  - While `input[*i]` exists and is whitespace, increments `*i`.
  - Stops when it hits a non-whitespace character or `\0`.
- **In the Example**:
  - `*i = 5` (space after `echo`): Increments to `*i = 6` (`"`).
  - `*i = 18` (space after `"`): Increments to `*i = 19` (`|`).
  - `*i = 20` (space after `|`): Increments to `*i = 21` (`c`).
  - No action at `*i = 0`, `*i = 6`, `*i = 19`, `*i = 21` (non-whitespace).

### ft_handle_word
- **Purpose**: Extracts an unquoted word from the input and creates a `TOKEN_WORD` token.
- **Variables**:
  - `t_shell *shell`: Shell context.
  - `const char *input`: The input string.
  - `size_t *i`: Pointer to the current index.
  - `size_t len`: Length of the word, calculated internally.
  - `t_token *token`: The new token created.
- **Process**:
  - Calls a helper `ft_get_word_length(input, *i)` to count characters until a space, operator, quote, or `\0`.
  - Calls `ft_create_token(shell, TOKEN_WORD, &input[*i], len)` to build a token with the substring starting at `*i` for `len` characters.
  - If successful, increments `*i` by `len` to skip the word.
  - Returns the `token`, or `NULL` if creation fails.
- **In the Example**:
  - `*i = 0` (`e`): `len = 4` (`echo`), creates `[WORD: "echo"]`, `*i = 5`.
  - `*i = 21` (`c`): `len = 3` (`cat`), creates `[WORD: "cat"]`, `*i = 24`.

### ft_handle_quotes
- **Purpose**: Processes a quoted string, treating its contents as a single `TOKEN_WORD`.
- **Variables**:
  - `t_shell *shell`: Shell context.
  - `const char *input`: The input string.
  - `size_t *i`: Pointer to the current index.
  - `size_t len`: Length of the quoted content.
  - `char *value`: Temporary string for the quoted content.
  - `t_token *token`: The new token.
  - `char quote`: The quote type (`"` or `'`).
- **Process**:
  - Sets `quote` to `input[*i]` (`"` or `'`), then increments `*i` past the opening quote.
  - Helper `ft_extract_quoted_string(shell, input, i, &len)` scans until the closing quote, setting `len` and returning `value` (or `NULL` if unclosed).
  - Creates `token` with `ft_create_token(shell, TOKEN_WORD, value, len)`.
  - Frees `value` (temporary allocation), then adjusts `*i` to skip the content plus closing quote.
  - Returns `token`, or `NULL` on failure.
- **In the Example**:
  - `*i = 6` (`"`): `quote = '"'`, `*i = 7`, `len = 11` (`hello world`), `value = "hello world"`, creates `[WORD: "hello world"]`, `*i = 18`.

### ft_handle_operator
- **Purpose**: Identifies and creates tokens for operators (`|`, `<`, `>`).
- **Variables**:
  - `t_shell *shell`: Shell context.
  - `const char *input`: The input string.
  - `size_t *i`: Pointer to the current index.
  - `t_token *token`: The new token.
- **Process**:
  - Helper `ft_is_operator(input[*i])` checks if the character is `|`, `<`, or `>`.
  - If true, calls `ft_create_token(shell, TOKEN_END, &input[*i], 1)` (type gets set to `TOKEN_PIPE`, etc., by `ft_create_token` logic).
  - Increments `*i` past the operator.
  - Returns `token`, or `NULL` if not an operator or creation fails.
- **In the Example**:
  - `*i = 19` (`|`): Recognizes `|`, creates `[PIPE: "|"]`, `*i = 20`.

### ft_create_token
- **Purpose**: Allocates and initializes a `t_token` struct with a type and value.
- **Variables**:
  - `t_shell *shell`: Shell context for memory tracking.
  - `t_token_type type`: The intended type (e.g., `TOKEN_END`, passed as a hint).
  - `const char *value`: The string content (e.g., `"echo"`, `"|"`).
  - `size_t len`: Length of `value` to copy.
  - `t_token *token`: The new token struct.
- **Process**:
  - Allocates `token` with `ft_track_malloc(shell, sizeof(t_token))`.
  - Allocates and copies `token->value` with `ft_track_strndup(shell, value, len)`.
  - If `type` is `TOKEN_END`, sets `token->type = TOKEN_END`; otherwise, uses helper `ft_set_token_type(value)` to determine `TOKEN_WORD`, `TOKEN_PIPE`, etc., based on `value`.
  - Sets `token->next = NULL`.
  - Returns `token`, or `NULL` if allocation fails (frees partial allocations).
- **In the Example**:
  - For `echo`: `type = TOKEN_WORD`, `value = "echo"`, `len = 4`, sets `type = TOKEN_WORD`.
  - For `"hello world"`: `type = TOKEN_WORD`, `value = "hello world"`, `len = 11`.
  - For `|`: `type = TOKEN_END` (overridden by `ft_set_token_type`), `value = "|"`, `len = 1`, sets `type = TOKEN_PIPE`.
  - For `cat`: `type = TOKEN_WORD`, `value = "cat"`, `len = 3`.
  - For end: `type = TOKEN_END`, `value = ""`, `len = 0`.

### ft_add_token
- **Purpose**: Adds a new `t_token` to the linked list, updating `head` and `tail`.
- **Variables**:
  - `t_token **head`: Pointer to the list’s head pointer.
  - `t_token **tail`: Pointer to the list’s tail pointer.
  - `t_token *new_token`: The token to add.
- **Process**:
  - If `new_token` is `NULL`, does nothing and returns.
  - If `*head` is `NULL` (empty list), sets `*head = new_token` and `*tail = new_token`.
  - Otherwise, links `(*tail)->next = new_token` and updates `*tail = new_token`.
- **In the Example**:
  - `*i = 0`: `new_token = [WORD: "echo"]`, `*head = NULL`, sets `*head = *tail = [WORD: "echo"]`.
  - `*i = 6`: `new_token = [WORD: "hello world"]`, `*tail->next = new_token`, `*tail = new_token`.
  - `*i = 19`: `new_token = [PIPE: "|"]`, `*tail->next = new_token`, `*tail = new_token`.
  - `*i = 21`: `new_token = [WORD: "cat"]`, `*tail->next = new_token`, `*tail = new_token`.

### ft_finalize_tokens
- **Purpose**: Appends a `TOKEN_END` token to mark the list’s end.
- **Variables**:
  - `t_shell *shell`: Shell context.
  - `t_token *head`: The current list head.
  - `t_token *end`: The new end token.
  - `t_token *tail`: Temporary pointer to find the list’s end.
- **Process**:
  - Creates `end` with `ft_create_token(shell, TOKEN_END, "", 0)`.
  - If `end` fails, calls `ft_free_tokens(shell, &head)` and returns `NULL`.
  - Sets `tail = head`, then loops until `tail->next` is `NULL` to find the list’s end.
  - Calls `ft_add_token(&head, &tail, end)` to append `end`.
  - Returns `head`.
- **In the Example**:
  - `head = [WORD: "echo"] -> ... -> [WORD: "cat"]`, creates `end = [END: ""]`.
  - Finds `tail = [WORD: "cat"]`, adds `end`, list becomes `[WORD: "echo"] -> ... -> [END: ""]`.
