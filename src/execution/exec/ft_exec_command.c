/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:17 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 16:56:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

static int	get_exit_code(pid_t pid);

static int	dup_fd(t_command *cmd)
{	
	if (cmd->next && cmd->fd_pipe[1] != STDOUT_FILENO)
	{
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[1]);		
	}
	if (cmd->prev && cmd->prev->fd_pipe[0] != STDIN_FILENO)
	{
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
		close(cmd->prev->fd_pipe[0]);
	}
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	return (0);
}

void ft_exec_command(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		i;
	int old_fd[2];

	if (!ft_cmd_is_builtin(shell, cmd) && ft_get_path(shell, cmd) != 0)
	{
		cmd->exit_val = 127;
		perror("Path error");
		return ;
	}
	if (cmd->is_builtin)
	{
		old_fd[0] = dup(STDIN_FILENO);
		old_fd[1] = dup(STDOUT_FILENO);
		dup_fd(cmd);
		cmd->exit_val = ft_exec_builtin(shell, cmd);
		dup2(old_fd[0], STDIN_FILENO);
		dup2(old_fd[1], STDOUT_FILENO);
		close(old_fd[0]);
		close(old_fd[1]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup_fd(cmd);
			{
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
				cmd->exit_val = 127;
				exit(127);
			}
		}
		else
		{
			cmd->exit_val = get_exit_code(pid);
			// printf("Exit code: %d\n", cmd->exit_val);
		}
	}
}

static int	get_exit_code(pid_t pid)
{
	int	status;

	if (pid < 0)
	{
		perror("fork failed");
		return (255);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid failed");
		return (255);
	}
	if (WIFEXITED(status))
	{
        return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
    {
		return (128 + WTERMSIG(status));
	}
	return (255);
}
