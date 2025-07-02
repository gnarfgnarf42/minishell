/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:29:11 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 00:21:54 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define SH_PATH		"/bin/sh"
# define PATH_ENV		"PATH"
# define PATH_DELIMITER	':'
# define ARGS_MAX		100

# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <linux/limits.h>
# include <errno.h>
# include "parser.h"

typedef struct s_command
{
	char				*cmdname;
	char				**args;
	int					argsc;
	char				**envp;
	pid_t				pid;
	int					fd_in;
	int					fd_out;
	int					fd_pipe[2];
	int					exit_val;
	int					is_builtin;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

// ft_exec_shell.c
int			ft_exec_shell(t_shell *shell);

// ft_exec_command.c
void		ft_exec_command(t_shell *shell, t_command *cmd);
int			ft_cmd_is_builtin(t_shell *shell, t_command *cmd);
int			ft_exec_builtin(t_shell *shell, t_command *cmd);

// ft_exec_path.c
int			ft_get_path(t_shell *shell, t_command *cmd);
char		*get_next_path(char *path, char delim);
char		*get_full_path(t_shell *shell, t_command *cmd, char *cur_path);
int			search_in_path(t_shell *shell, t_command *cmd);
int			str_is_pathname(char *str);
int			path_is_dir(char *path);

// ft_proc_line.c
t_command	*ft_create_cmd_line(t_shell *shell);
t_token		*ft_process_token(t_shell *shell, t_token *token, t_command **cmd);

// ft_proc_word.c
t_token		*ft_process_word(t_shell *shell, t_token *token, t_command *cmd);
t_token		*ft_process_redir_in(t_shell *shell, t_token *token,
				t_command *cmd);
t_token		*ft_process_redir_out(t_shell *shell, t_token *token,
				t_command *cmd);
t_token		*ft_process_append(t_shell *shell, t_token *token, t_command *cmd);
t_token		*ft_process_heredoc(t_shell *shell, t_token *token, t_command *cmd);
t_token		*ft_process_pipe(t_shell *shell, t_token *token, t_command **cmd);

// utils/command.c
void		ft_print_cmd(t_command *cmd);
t_command	*ft_init_cmd(t_shell *shell);
void		ft_free_cmd(t_shell *shell, t_command *cmd);
void		ft_free_cmd_line(t_shell *shell, t_command *cmd);
// cmd
int			ft_ms_cd(t_shell *shell, t_command *cmd);
int			ft_ms_echo(t_shell *shell, t_command *cmd);
int			ft_ms_env(t_shell *shell, t_command *cmd);
void		ft_penv(t_shell *shell);
int			ft_ms_exit(t_shell *shell, t_command *cmd);
int			ft_ms_export(t_shell *shell, t_command *cmd);
int			ft_export_arg(t_shell *shell, t_command *cmd, char *arg);
int			ft_ms_pwd(t_shell *shell, t_command *cmd);
int			ft_ms_unset(t_shell *shell, t_command *cmd);

// utils/error.c
int			ft_perror(char *process, char *arg, char *message, int code);
int			ft_perror_syntax(char *arg);

// utils/fd.c
int			ft_close_cmd_fd(t_command *cmd);
int			ft_close_all_fd(t_shell *shell);
void		ft_dup_fd(t_command *cmd);

// utils/builtin.c

#endif