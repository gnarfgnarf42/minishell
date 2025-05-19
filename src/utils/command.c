/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:24:15 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/18 15:58:13 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_command	*ft_init_cmd(t_shell *shell)
{
	t_command	*cmd;

	cmd = (t_command *)ft_track_malloc(shell, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = ft_track_malloc(shell, sizeof(char *) * ARGS_MAX);
	if (!cmd->args)
		return (NULL);
	cmd->cmdname = NULL;
	cmd->argsc = 0;
	cmd->envp = shell->envp;
	cmd->exit_val = 0;
	cmd->is_builtin = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_pipe[0] = STDIN_FILENO;
	cmd->fd_pipe[1] = STDOUT_FILENO;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	ft_free_cmd(t_shell *shell, t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (cmd->fd_pipe[0] != STDIN_FILENO)
		close(cmd->fd_pipe[0]);
	if (cmd->fd_pipe[1] != STDOUT_FILENO)
		close(cmd->fd_pipe[1]);
	if (cmd && cmd->args)
		ft_track_free(shell, cmd->args);
	if (cmd)
		ft_track_free(shell, cmd);
}

void	ft_free_cmd_line(t_shell *shell, t_command *cmd)
{
	t_command	*cmd_next;

	while (cmd)
	{
		cmd_next = cmd->next;
		ft_free_cmd(shell, cmd);
		cmd = cmd_next;
	}
}

void	ft_print_cmd(t_command *cmd)
{
	char	**arg;

	arg = cmd->args;
	printf("\ncmd: '%s'\n", cmd->cmdname);
	printf("argsc: %d\nargs:", cmd->argsc);
	while (*arg)
	{
		if (arg != cmd->args)
			printf(",");
		printf(" '%s'", *arg);
		arg++;
	}
	printf("\nfd_in: %2d | fd_out: %d\n", cmd->fd_in, cmd->fd_out);
	printf("pipe: %3d | %d\n", cmd->fd_pipe[0], cmd->fd_pipe[1]);
	printf("next: %p\n", cmd->next);
	printf("prev: %p\n", cmd->prev);
}

// Check if cmdname is a build-in function
// Return 0 if yes and execution is success
// Return -1 if yes and execution with error
// Return 1 if cmdname is not a build-in function
int	ft_exec_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (!ft_strcmp(cmd->cmdname, "echo"))
		return (ft_ms_echo(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "cd"))
		return (ft_ms_cd(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "pwd"))
		return (ft_ms_pwd(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "export"))
		return (ft_ms_export(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "unset"))
		return (ft_ms_unset(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "env"))
		return (ft_ms_env(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "exit"))
		return (ft_ms_exit(shell, cmd));
	return (1);
}

int	ft_cmd_is_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (!ft_strcmp(cmd->cmdname, "echo"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "cd"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "pwd"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "export"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "unset"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "env"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "exit"))
		cmd->is_builtin = 1;
	return (cmd->is_builtin);
}

int	ft_close_cmd_fd(t_command *cmd)
{
	if (cmd->next && cmd->fd_pipe[1] != STDOUT_FILENO)
		close(cmd->fd_pipe[1]);
	if (cmd->prev && cmd->prev->fd_pipe[0] != STDIN_FILENO)
		close(cmd->prev->fd_pipe[0]);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	return (0);
}
