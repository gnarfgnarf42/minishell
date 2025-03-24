# Memory Tests Documentation

This document describes the unit tests for the memory management functions (`ft_track_malloc`, `ft_track_strdup`, `ft_track_free`) in the Minishell project. These functions are critical for tracking dynamic memory allocations to prevent leaks in a shell environment that handles variable-sized input and complex data structures like ASTs.

## Test File
- **Location**: `tests/unit/test_memory.c`
- **Framework**: Unity Test Framework
- **Binary**: `test_binary` (built via `make test`)

## Running the Tests
- **Normal Run**: `make test`
- **With Valgrind**: `make valgrind-test` (checks for memory leaks)

## Test Suite Overview
The tests ensure that memory allocation, string duplication, and deallocation work correctly, handle edge cases, and maintain the `t_shell->memory_list` linked list. They are run as part of the `test-memory` target.

---

## Tests for `ft_track_malloc`

### 1. `test_ft_track_malloc_basic`
- **What It Does**: Allocates 10 bytes, checks the returned pointer, and verifies tracking in `memory_list`.
- **Why**: Confirms the core functionality of allocating and tracking memory, the foundation for all tracked allocations in Minishell.
- **Checks**: Non-`NULL` pointer, correct `ptr` and `size` (10) in the list, single-node list.

### 2. `test_ft_track_malloc_zero_size`
- **What It Does**: Allocates 0 bytes, verifies behavior (currently allows a valid pointer).
- **Why**: Ensures edge case handling for zero-size requests, which might occur with empty inputs or miscalculations.
- **Checks**: Non-`NULL` pointer (adjustable to `NULL` if preferred), size 0 tracked if allocated.

### 3. `test_ft_track_malloc_large`
- **What It Does**: Allocates 1024 bytes, checks the allocation and tracking.
- **Why**: Tests scalability for larger buffers (e.g., long command inputs in Minishell).
- **Checks**: Non-`NULL` pointer, correct size (1024) in `memory_list`.

### 4. `test_ft_track_malloc_list_integration`
- **What It Does**: Allocates 8 bytes, verifies the `memory_list` node details.
- **Why**: Ensures proper integration with the tracking system, critical for leak prevention.
- **Checks**: List exists, correct `ptr` and `size`, `next` is `NULL`.

### 5. `test_ft_track_malloc_multiple`
- **What It Does**: Allocates three blocks (5, 10, 15 bytes), frees one, checks list integrity.
- **Why**: Validates list management with multiple allocations, mimicking real shell usage with many allocations.
- **Checks**: All pointers non-`NULL`, list order preserved, middle free updates links correctly.

---

## Tests for `ft_track_strdup`

### 1. `test_ft_track_strdup_basic`
- **What It Does**: Duplicates "hello", checks the result and length.
- **Why**: Verifies basic string duplication, a common operation in shell input handling.
- **Checks**: Non-`NULL`, matches "hello", length 5, list cleaned up.

### 2. `test_ft_track_strdup_empty`
- **What It Does**: Duplicates "", checks the empty string and allocation.
- **Why**: Ensures empty inputs (e.g., empty commands) are handled, testing minimal allocation.
- **Checks**: Non-`NULL`, empty string, length 0, 1-byte allocation.

### 3. `test_ft_track_strdup_null`
- **What It Does**: Passes `NULL`, checks the result.
- **Why**: Tests error handling for invalid inputs, preventing crashes in edge cases.
- **Checks**: Returns `NULL`, no allocation in `memory_list`.

### 4. `test_ft_track_strdup_long`
- **What It Does**: Duplicates a long string, checks accuracy and size.
- **Why**: Ensures robustness with larger inputs (e.g., long commands or arguments).
- **Checks**: Non-`NULL`, matches original, correct length, size tracked.

### 5. `test_ft_track_strdup_memory_tracking`
- **What It Does**: Duplicates "track me", checks `memory_list` details.
- **Why**: Confirms `ft_track_malloc` integration within `ft_track_strdup`.
- **Checks**: Pointer and size match, single-node list.

### 6. `test_ft_track_strdup_multiple`
- **What It Does**: Duplicates two strings ("first", "second"), frees one, checks list.
- **Why**: Tests list growth and partial freeing, ensuring stability with multiple strings.
- **Checks**: Both strings duplicated, list order correct, freeing updates list.

---

## Tests for `ft_track_free`

### 1. `test_ft_track_free_basic`
- **What It Does**: Allocates 10 bytes, frees it, checks the list.
- **Why**: Validates the simplest free operation, ensuring memory is released.
- **Checks**: List becomes `NULL` after freeing.

### 2. `test_ft_track_free_null`
- **What It Does**: Allocates 5 bytes, tries freeing `NULL`, checks list.
- **Why**: Ensures `NULL` inputs are ignored, a common C convention.
- **Checks**: List unchanged after `NULL` free.

### 3. `test_ft_track_free_non_existent`
- **What It Does**: Allocates 8 bytes, tries freeing a random pointer, checks list.
- **Why**: Prevents crashes or corruption from invalid pointers (e.g., user errors).
- **Checks**: List unchanged.

### 4. `test_ft_track_free_middle`
- **What It Does**: Allocates three blocks (5, 10, 15 bytes), frees the middle one.
- **Why**: Tests list linking when removing a non-head node, critical for complex freeing.
- **Checks**: List reconnected correctly (head → tail).

### 5. `test_ft_track_free_multiple`
- **What It Does**: Allocates three blocks, frees in mixed order (first, head, last).
- **Why**: Ensures list integrity with multiple frees, simulating shell cleanup.
- **Checks**: List updates correctly at each step.

### 6. `test_ft_track_free_double`
- **What It Does**: Allocates 20 bytes, frees it twice.
- **Why**: Prevents crashes from double-free bugs, a common memory error.
- **Checks**: Second free does nothing, list stays `NULL`.

---

## Tests for `ft_track_free`

### 1. `test_ft_track_free_basic`
- **What It Does**: Allocates 10 bytes with `ft_track_malloc`, frees it with `ft_track_free`, checks the list.
- **Why**: Ensures the basic functionality of freeing a single allocation and updating the tracking list.
- **Checks**: List becomes `NULL` after freeing.

### 2. `test_ft_track_free_null`
- **What It Does**: Allocates 5 bytes, tries freeing `NULL`, checks the list.
- **Why**: Verifies that passing `NULL` is safely ignored, a common C convention to avoid crashes.
- **Checks**: List remains unchanged, original allocation still tracked.

### 3. `test_ft_track_free_non_existent`
- **What It Does**: Allocates 8 bytes, tries freeing a random pointer (e.g., `0x1234`), checks the list.
- **Why**: Ensures the function doesn’t crash or corrupt the list when given an untracked pointer, protecting against invalid inputs.
- **Checks**: List remains intact with the original allocation.

### 4. `test_ft_track_free_middle`
- **What It Does**: Allocates three blocks (5, 10, 15 bytes), frees the middle one (10 bytes), checks list structure.
- **Why**: Tests list manipulation when removing a node that’s not at the head, ensuring proper reconnection.
- **Checks**: List re-links correctly (head → tail), middle node removed.

### 5. `test_ft_track_free_multiple`
- **What It Does**: Allocates three blocks (5, 10, 15 bytes), frees them in mixed order (first, head, last).
- **Why**: Confirms list integrity across multiple frees, simulating selective cleanup in Minishell.
- **Checks**: List updates correctly at each step, all memory freed.

### 6. `test_ft_track_free_double`
- **What It Does**: Allocates 20 bytes, frees it, tries freeing it again.
- **Why**: Prevents crashes from double-free errors, a common bug in memory management.
- **Checks**: Second free has no effect, list stays `NULL`, no crash.

---

## Reasoning Behind the Tests
- **Correctness**: Basic tests (`basic`, `large`, `multiple`) ensure the functions work as intended for typical use in Minishell (e.g., command processing).
- **Edge Cases**: `zero_size`, `null`, `non_existent`, and `empty` handle unusual or invalid inputs that might arise from user input or bugs.
- **Robustness**: `long`, `multiple`, and `middle` test scalability and list management, preparing for Minishell’s dynamic memory needs (e.g., parsing long commands or managing many allocations).
- **Safety**: `double` and `non_existent` protect against crashes or corruption, ensuring stability in a shell environment.
- **Leak Prevention**: All tests use `ft_free_all_tracked` and are checked with `valgrind-memory` to guarantee no memory leaks.

## Future Additions
- Integration tests combining memory functions with parsing or execution logic.
- Mocking for allocation failures (advanced, optional).

---
