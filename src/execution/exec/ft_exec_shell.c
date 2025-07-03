/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:59 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 14:32:00 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

static void	wait_child_procs(t_command	*cmd)
{
	int			status;

	while (cmd)
	{
		if (cmd->pid < 0)
		{
			cmd = cmd->next;
			continue ;
		}
		if (waitpid(cmd->pid, &status, 0) == -1)
		{
			ft_perror("minishell", cmd->cmdname, strerror(errno));
			cmd->exit_val = 255;
		}
		if (WIFEXITED(status))
		{
			cmd->exit_val = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			cmd->exit_val = 128 + WTERMSIG(status);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		cmd = cmd->next;
	}
}

static void	close_bad_cmd_fds(t_command *cmd)
{
	if (cmd->fd_pipe[1] != STDOUT_FILENO)
		close(cmd->fd_pipe[1]);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

int	ft_exec_shell(t_shell *shell)
{
	shell->cmd_list = ft_create_cmd_line(shell);
	if (!shell->cmd_list)
		return (1);
	ft_set_cmd_builtin(shell);
	ft_exec_commands(shell);
	ft_close_all_fd(shell);
	wait_child_procs(shell->cmd_list);
	ft_write_exit_code(shell);
	ft_free_cmd_line(shell);
	return (0);
}

void	ft_exec_commands(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->exit_val != 0)
		{
			close_bad_cmd_fds(cmd);
		}
		else if (cmd->is_builtin)
		{
			if (ft_exec_builtin(shell, cmd))
				break ;
		}
		else if (ft_get_path(shell, cmd) == 0)
		{
			if (ft_exec_external(shell, cmd))
				break ;
		}
		cmd = cmd->next;
	}
}
