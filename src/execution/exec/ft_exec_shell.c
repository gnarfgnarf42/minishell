/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:59 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 12:23:17 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include <errno.h>
#include <signal.h>

static void	write_exit_code(t_shell *shell)
{
	t_command	*cmd;
	
	if (!shell)
		return ;
	cmd = shell->cmd_list;
	while (cmd->next)
		cmd = cmd->next;
	shell->last_exit_status = cmd->exit_val;
	return ;
}

static void	dup_fd(t_command *cmd)
{
	if (cmd->next && cmd->fd_pipe[1] != STDOUT_FILENO)
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
	if (cmd->prev && cmd->prev->fd_pipe[0] != STDIN_FILENO)
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
}

int	ft_exec_shell(t_shell *shell)
{
	t_command	*cmd;
	int			i;
	int			status;
	int			old_fd[2];

	shell->cmd_list = ft_create_cmd_line(shell);
	if (!shell->cmd_list)
		return (1);
	
	// Check if cmd is builtin and set cmd->is_builtin
	cmd = shell->cmd_list;
	while (cmd)
	{
		ft_cmd_is_builtin(shell, cmd);
		cmd = cmd->next;
	}
	// Create fork. Put PID to cmd->pid
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->exit_val != 0)
		{
			cmd = cmd->next;
			continue;
		}
		if (cmd->is_builtin)
		{
			if (cmd->next || cmd->prev) // If builtin in pipeline -> make fork
			{
				// ft_putstr_fd("Builtin in pipe\n", STDOUT_FILENO);
				cmd->pid = fork();
				if (cmd->pid < 0)
				{
					cmd->exit_val = 255;
					perror("fork failed");
					return (1);
				}
				if (cmd->pid == 0)
				{
					signal(SIGQUIT, SIG_DFL);
					signal(SIGINT, SIG_DFL);
					dup_fd(cmd);
					ft_close_all_fd(shell);
					cmd->exit_val = ft_exec_builtin(shell, cmd);
					exit(cmd->exit_val);
				}
			}
			else // If builtin is alone -> run in current process
			{
				old_fd[0] = dup(STDIN_FILENO);
				old_fd[1] = dup(STDOUT_FILENO);
				dup_fd(cmd);
				cmd->exit_val = ft_exec_builtin(shell, cmd);
				// printf("BUILTIN cmd->exit_val: %i\n", cmd->exit_val);
				dup2(old_fd[0], STDIN_FILENO);
				dup2(old_fd[1], STDOUT_FILENO);
				close(old_fd[0]);
				close(old_fd[1]);
			}
		}
		else if (ft_get_path(shell, cmd) != 0)
		{
			cmd = cmd->next;
			continue;
		}
		else
		{
			cmd->pid = fork();
			if (cmd->pid < 0) // Fork error
			{
				cmd->exit_val = 255;
				perror("fork failed");
				return (1);
			}
			if (cmd->pid == 0) // Child process
			{
				signal(SIGQUIT, SIG_DFL); // Restore default handler
				signal(SIGINT, SIG_DFL);
				dup_fd(cmd);
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
				exit(cmd->exit_val);
			}
		}
		cmd = cmd->next;
	}
	// Parent closes all pipe fds
	ft_close_all_fd(shell);
    // Wait for all children and store exit codes
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->pid < 0)
		{
			cmd = cmd->next;
			continue;
		}
		if (waitpid(cmd->pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			ft_putchar_fd('\n', STDOUT_FILENO);
			cmd->exit_val = 255;
		}
		if (WIFEXITED(status))
		{
			cmd->exit_val = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			cmd->exit_val = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}

	write_exit_code(shell);
	ft_close_all_fd(shell);
	ft_free_cmd_line(shell, shell->cmd_list);
	return (0);
}
