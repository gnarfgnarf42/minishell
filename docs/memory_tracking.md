# Memory Tracking in Minishell

## **Overview**
Minishell requires dynamic memory allocation for handling commands, environment variables, and user inputs. To ensure **no memory leaks** while complying with the **42 Norm**, we implement a **manual memory tracking system** without using global variables.

This document explains the tracking system, necessary functions, and how it integrates with `readline()`.

---

## **1. Memory Tracking System**
### **Why Use a Memory Tracking System?**
- Ensures all allocated memory is freed properly.
- Prevents memory leaks and double-free errors.
- Simplifies cleanup by freeing everything at once.

### **Key Design Constraints**
- **No global variables** (except for the signal handler).
- **Each allocation is tracked** inside `t_shell`.
- **Memory is freed at shell exit and after command execution**.

### **Tracking Structure (`t_mem_node`)**
We maintain a **linked list** to store allocated memory addresses:
```c
typedef struct s_mem_node {
    void *ptr;
    struct s_mem_node *next;
} t_mem_node;

typedef struct s_shell {
    t_mem_node *mem_list;  // Memory tracking list
    char **env;            // Environment variables
} t_shell;
```

### **Allocating and Tracking Memory (`track_malloc`)**
Instead of using `malloc()` directly, we use `track_malloc()`:
```c
void *track_malloc(t_shell *shell, size_t size) {
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;
    
    t_mem_node *new_node = malloc(sizeof(t_mem_node));
    if (!new_node) {
        free(ptr);
        return NULL;
    }

    new_node->ptr = ptr;
    new_node->next = shell->mem_list;
    shell->mem_list = new_node;
    
    return ptr;
}
```
✅ **Ensures every allocated pointer is tracked.**

### **Freeing Memory (`free_all`)**
This function ensures **all tracked memory is freed** at shell exit:
```c
void free_all(t_shell *shell) {
    t_mem_node *tmp;
    while (shell->mem_list) {
        tmp = shell->mem_list;
        shell->mem_list = shell->mem_list->next;
        free(tmp->ptr);
        free(tmp);
    }
}
```
✅ **Prevents memory leaks by freeing everything in one call.**

### **Free a Specific Pointer (`tracked_free`)**
To safely free a single pointer:
```c
void tracked_free(t_shell *shell, void *ptr) {
    t_mem_node *prev = NULL;
    t_mem_node *curr = shell->mem_list;
    
    while (curr) {
        if (curr->ptr == ptr) {
            if (prev)
                prev->next = curr->next;
            else
                shell->mem_list = curr->next;
            
            free(curr->ptr);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
```
✅ **Prevents double-free errors and keeps the tracking list clean.**

---

## **2. Readline Integration**
`readline()` dynamically allocates memory for user input. However:
- It does **not automatically free returned strings**.
- It keeps some internal memory allocated for history.

### **Handling Readline Memory**
#### **Freeing Each Input String**
```c
char *line = readline("minishell> ");
if (line)
    free(line);  // Prevents memory leaks
```
✅ **Essential for avoiding memory leaks from repeated readline calls.**

#### **Clearing Readline History**
If using `add_history(line)`, it keeps history in memory. Use:
```c
rl_clear_history();
```
✅ **Frees stored command history at shell exit.**

#### **Freeing History Entries (Optional)**
For finer control over memory:
```c
#include <readline/history.h>

void free_history_entries() {
    HIST_ENTRY *entry;
    while ((entry = remove_history(0))) {
        free(entry->line);
        free(entry);
    }
}
```
✅ **Frees all stored history manually.**

### **Resetting Readline (Optional)**
```c
rl_reset_terminal(NULL);
```
✅ **Resets terminal settings but does not fully free all buffers.**

---

## **3. Full Cleanup on Shell Exit**
When the user exits, call this:
```c
void cleanup_shell(t_shell *shell) {
    free_all(shell);       // Free tracked memory
    rl_clear_history();    // Free readline history
}
```
✅ **Ensures no memory leaks at shell termination.**

---

## **4. Summary of Functions**
| Function | Purpose |
|----------|---------|
| `track_malloc()` | Allocates and tracks memory |
| `tracked_free()` | Frees a specific tracked pointer |
| `free_all()` | Frees all tracked memory at shell exit |
| `free_history_entries()` | Manually frees readline history |
| `cleanup_shell()` | Final cleanup function for exit |

---

## **Conclusion**
This tracking system ensures **Minishell has no memory leaks** while **complying with the 42 Norm**. It integrates seamlessly with `readline()`, managing its returned memory without interfering with its internal behavior.

🚀 **Implementing this from the start will make debugging easier and prevent memory-related crashes!**

---

To go back to our development process, see our [Project Approach](project_approach.md).

