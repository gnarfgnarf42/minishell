/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:17 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/05 11:23:12 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>
#include <signal.h>

void	builtin_in_child_proc(t_shell *shell, t_command *cmd)
{
	int	ev;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	ft_dup_fd(cmd);
	ft_close_all_fd(shell);
	cmd->exit_val = ft_run_builtin_cmd(shell, cmd);
	ev = cmd->exit_val;
	ft_free_all_tracked(shell);
	exit(ev);
}

void	builtin_in_current_proc(t_shell *shell, t_command *cmd)
{
	int			old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	ft_dup_fd(cmd);
	cmd->exit_val = ft_run_builtin_cmd(shell, cmd);
	dup2(old_fd[0], STDIN_FILENO);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[0]);
	close(old_fd[1]);
}

int	ft_exec_builtin(t_shell *shell, t_command *cmd)
{
	if (cmd->next || cmd->prev)
	{
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			cmd->exit_val = 255;
			perror("fork failed");
			return (1);
		}
		if (cmd->pid == 0)
		{
			builtin_in_child_proc(shell, cmd);
		}
	}
	else
	{
		builtin_in_current_proc(shell, cmd);
	}
	return (0);
}

void	execve_in_child_proc(t_shell *shell, t_command *cmd)
{
	int			i;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	ft_dup_fd(cmd);
	ft_close_all_fd(shell);
	execve(cmd->cmdname, cmd->args, cmd->envp);
	if (errno == ENOEXEC)
	{
		i = 0;
		while (cmd->args[i])
			i++;
		while (i >= 0)
		{
			cmd->args[i + 1] = cmd->args[i];
			i--;
		}
		cmd->args[0] = SH_PATH;
		execve(SH_PATH, cmd->args, cmd->envp);
	}
	perror("execve failed");
	cmd->exit_val = 126;
	ft_free_all_tracked(shell);
	exit(cmd->exit_val);
}

int	ft_exec_external(t_shell *shell, t_command *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		cmd->exit_val = 255;
		perror("fork failed");
		return (1);
	}
	if (cmd->pid == 0)
	{
		execve_in_child_proc(shell, cmd);
	}
	return (0);
}
