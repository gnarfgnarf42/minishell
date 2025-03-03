 Git Cheat Sheet for Minishell

## 🔹 1. Basic Git Commands
| **Action** | **Command** |
|-----------|------------|
| Check current branch & status | `git status` |
| Show commit history | `git log --oneline --graph --all` |
| See the last changes made | `git diff` |

## 🔹 2. Working with Branches
| **Action** | **Command** |
|-----------|------------|
| Create a new branch | `git checkout -b feature/new-thing` |
| Switch to a branch | `git checkout dev` |
| List all branches | `git branch` |
| Push a branch to GitHub | `git push origin feature/new-thing` |
| Delete a branch (after merging) | `git branch -d feature/new-thing` |
| Delete a remote branch | `git push origin --delete feature/new-thing` |

## 🔹 3. Keeping Everything Up to Date
| **Action** | **Command** |
|-----------|------------|
| Fetch latest changes | `git fetch origin` |
| Update your current branch | `git pull origin dev` |
| Update & switch to dev | `git checkout dev && git pull origin dev` |

## 🔹 4. Staging & Committing Changes
| **Action** | **Command** |
|-----------|------------|
| Add all changes | `git add .` |
| Add a specific file | `git add file.c` |
| Commit with a message | `git commit -m "feat: added parser"` |
| Commit only staged changes | `git commit` (opens editor) |

## 🔹 5. Pushing & Merging Code
| **Action** | **Command** |
|-----------|------------|
| Push your branch to GitHub | `git push origin feature/parser` |
| Merge a branch into dev | `git checkout dev && git merge feature/parser` |
| Push `dev` to GitHub | `git push origin dev` |
| Create a Pull Request (PR) | Do it on GitHub! |

## 🔹 6. Handling Merge Conflicts
| **Action** | **Command** |
|-----------|------------|
| Check for conflicts | `git status` |
| Open the conflicting file & fix it manually | Edit in your code editor |
| Mark the conflict as resolved | `git add file.c` |
| Commit the resolution | `git commit -m "fix: resolved merge conflict"` |
| Push the resolved branch | `git push origin dev` |

## 🔹 7. Undo Mistakes (Carefully!)
| **Action** | **Command** |
|-----------|------------|
| Undo unstaged changes | `git checkout -- file.c` |
| Undo the last commit (keep changes) | `git reset --soft HEAD~1` |
| Undo the last commit (delete changes) | `git reset --hard HEAD~1` |

## 🎯 Best Practices
✅ **Always pull (`git pull origin dev`) before starting work** 
✅ **Work in feature branches, not `dev`** 
✅ **Commit often with meaningful messages** 
✅ **Use `git status` frequently to check your work** 
✅ **Review & test before merging into `dev`** 
---
