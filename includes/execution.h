/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:21:49 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/07 19:29:55 by nefimov          ###   ########.fr       */
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
# include "parser.h"

typedef struct s_command
{
	char 				*cmdname;
	char 				**args;
	int 				argsc;
	char				**envp;
	int					fd_in;
	int					fd_out;
	int					exit_val;
	struct s_command	*next;
}	t_command;

t_command	*init_cmd(t_shell *shell);
void		ft_exec_command(t_shell *shell, t_command *cmd);

t_command	*ft_create_exec_line(t_shell *shell);
t_token		*ft_process_token(t_shell *shell, t_token *token, t_command *cmd);

int			ft_get_path(t_shell *shell, t_command *cmd);
char		*get_next_path(char *path, char delim);
char		*get_full_path(t_shell *shell, t_command *cmd, char *cur_path);
int 		search_in_path(t_shell *shell, t_command *cmd);
int			str_is_pathname(char *str);
int			path_is_dir(char *path);


#endif