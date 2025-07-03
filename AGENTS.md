Norm and Minishell Rules for CLI Compliance
This document outlines the coding rules from The Norm (Version 4.1) and the Minishell project (Version 8.3) to be strictly followed for all C code submissions. These rules ensure code clarity, maintainability, and compliance with the 42 school's standards. All rules must be adhered to under any circumstances when generating code for the Minishell project.
Norm Rules for Function Size, File Size, Variables, Parameters, and Initialization
Function Size

Maximum Function Length: Each function must be at most 25 lines long, excluding the function's opening and closing braces.
Single Task per Function: Functions must perform a single, clear task to ensure readability and avoid complexity.
Parameter Limit: A function can have at most 4 named parameters.
Void Parameters: A function with no arguments must be explicitly prototyped with void as the argument.
Return Statement: Function return values must be enclosed in parentheses, unless the function returns nothing.
Tabulation: A single tabulation (ASCII char 9) must separate the return type and function name in declarations.

File Size

Maximum Functions per File: A .c file can contain at most 5 function definitions.
No C File Inclusion: Including a .c file in another .c file is forbidden.

Variables

Variable Limit: A function can declare at most 5 variables.
Global Variables: Global variables must be const or static unless explicitly allowed by the project. Non-compliant global variables are considered a norm error.
Naming: Variable names must:
Use snake_case (lowercase, digits, and underscores only; no capital letters).
Be explicit or mnemonic, readable in English, with words separated by underscores.


Declaration Placement: All variable declarations must be at the beginning of a function.
Single Declaration per Line: Only one variable declaration per line is allowed.
Initialization: Variable declaration and initialization cannot be on the same line, except for global variables (when allowed), static variables, and constants.
Pointer Asterisks: Asterisks for pointers must be attached to the variable name (e.g., int *ptr).
Indentation: All variable names within the same scope must be aligned on the same column, with types indented by the containing block.

General Formatting

Line Length: Each line must be at most 80 columns wide, including comments. Tabs count as the number of spaces they represent.
Indentation: Use 4-character tabulations (ASCII char 9) for indentation. Blocks within braces must be indented, and braces must be on their own line (except for struct, enum, or union declarations).
Empty Lines: 
An empty line must be completely empty (no spaces or tabs).
No two consecutive empty lines are allowed.
Functions must be separated by one empty line, though comments or preprocessor directives may be inserted.
An empty line is required between variable declarations and the rest of a function's code.


Spacing:
No trailing spaces or tabs at the end of a line.
No two consecutive spaces.
Commas and semicolons must be followed by a single space unless at the end of a line.
Operators and operands must be separated by exactly one space.
C keywords (except type keywords like int, char, etc., and sizeof) must be followed by a space.


Instruction Limits: Only one instruction or control structure per line. Assignments within control structures or multiple assignments on the same line are forbidden.
Splitting Lines: Long instructions can be split across multiple lines, with subsequent lines indented using natural spaces. Operators should start the new line, not end the previous one.

Minishell-Specific Rules
General Requirements

Language: The project must be written in C.
Norm Compliance: All code, including bonus files/functions, must comply with The Norm. Any norm error results in a score of 0.
Stability: Functions must not cause unexpected crashes (e.g., segmentation faults, bus errors, double frees) except for undefined behavior. Such issues result in a score of 0.
Memory Management: All heap-allocated memory must be properly freed to avoid memory leaks. Memory leaks in the readline() function are exempt, but leaks in your own code are not tolerated.
Global Variables: At most one global variable is allowed, used solely to store a received signal number. It must not provide additional information or access to data structures. Using "norm" type structures in global scope is forbidden.

Makefile Requirements

Mandatory Rules: The Makefile must include $(NAME), all, clean, fclean, and re. The all rule must be the default and execute when running make.
Compiler Flags: Compile with cc using -Wall, -Wextra, and -Werror.
No Unnecessary Relinking: The Makefile must not relink when not needed, or the project is considered non-functional.
Source Files: All source files must be explicitly named in the Makefile (e.g., no *.c or *.o wildcards).
Libft: If using libft, copy its sources and Makefile into a libft folder. The project's Makefile must compile libft using its Makefile before compiling the project.
Bonus Rule: For bonuses, include a bonus rule in the Makefile to compile bonus files (in _bonus.{c/h} files unless specified otherwise).

Shell Functionality
The minishell program must:

Prompt: Display a prompt when waiting for a new command.
History: Maintain a working command history.
Executable Search: Launch executables based on the PATH variable or using relative/absolute paths.
Quotes:
Do not interpret unclosed quotes or special characters like \ or ;.
Handle single quotes (') to prevent interpretation of metacharacters in the quoted sequence.
Handle double quotes (") to prevent interpretation of metacharacters except for $ (dollar sign).


Redirections:
< redirects input.
> redirects output.
<< reads input until a specified delimiter is seen (without updating history).
>> redirects output in append mode.


Pipes: Implement | to connect the output of one command to the input of the next.
Environment Variables: Expand $ followed by a sequence of characters to their values and $? to the exit status of the most recently executed foreground pipeline.
Signal Handling (in interactive mode):
Ctrl-C: Display a new prompt on a new line.
Ctrl-D: Exit the shell.
Ctrl-\: Do nothing.


Built-in Commands:
echo with -n option.
cd with only relative or absolute paths.
pwd with no options.
export with no options.
unset with no options.
env with no options or arguments.
exit with no options.



Allowed External Functions
The following functions are permitted:

readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
printf, malloc, free, write, access, open, read, close
fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit
getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe
opendir, readdir, closedir, strerror, perror
isatty, ttyname, ttyslot, ioctl
getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
Functions from libft (if used).

Bonus Requirements

Bonuses will only be evaluated if the mandatory part is fully implemented and functional.
Implement:
&& and || with parentheses for priority.
Wildcards (*) for the current working directory.



Submission

Submit all work in the assigned Git repository.
Ensure file names are correct.
Only work in the repository will be graded.

Additional Notes

Norminette: Use the norminette tool (available at https://github.com/42School/norminette) to check compliance. Rules marked with (*) are not checked by norminette but can lead to project failure if violated during code review.
Reference: Use bash as a reference for any unclear requirements.
Testing: Create test programs to validate your work, though they are not submitted or graded.

Compliance Directive
All generated C code for the Minishell project must strictly adhere to these rules. Any deviation, including norm errors, memory leaks, or non-compliance with formatting, naming, or functional requirements, will result in invalid code. Ensure all code is clear, maintainable, and aligns with the pedagogical goals of simplicity and readability as outlined in The Norm.