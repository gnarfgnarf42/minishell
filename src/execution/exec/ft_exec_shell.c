/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:59 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 13:30:11 by nefimov          ###   ########.fr       */
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

int	ft_exec_shell(t_shell *shell)
{
	t_command	*cmd;
	int			i;
	// int			status;
	int			old_fd[2];

	shell->cmd_list = ft_create_cmd_line(shell);
	if (!shell->cmd_list)
		return (1);
	// Check if cmd is builtin and set cmd->is_builtin
	ft_set_cmd_builtin(shell);
	// Execute commands in shell->cmd_list
	cmd = shell->cmd_list;
	while (cmd)
	{
		// ft_print_cmd(cmd);
		if (cmd->exit_val != 0)
		{
			// Close pipe write end to prevent broken pipe for next command
			if (cmd->fd_pipe[1] != STDOUT_FILENO)
				close(cmd->fd_pipe[1]);
			// Close redirection file descriptors
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			if (cmd->fd_out != STDOUT_FILENO)
				close(cmd->fd_out);
			cmd = cmd->next;
			continue ;
		}
		if (cmd->is_builtin)
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
					signal(SIGQUIT, SIG_DFL);
					signal(SIGINT, SIG_DFL);
					signal(SIGPIPE, SIG_DFL);
					// signal(SIGPIPE, SIG_IGN);
					ft_dup_fd(cmd);
					ft_close_all_fd(shell);
					cmd->exit_val = ft_exec_builtin(shell, cmd);
					exit(cmd->exit_val);
				}
			}
			else // If builtin is alone -> run in current process
			{
				old_fd[0] = dup(STDIN_FILENO);
				old_fd[1] = dup(STDOUT_FILENO);
				ft_dup_fd(cmd);
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
			continue ;
		}
		else
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
				exit(cmd->exit_val);
			}
		}
		cmd = cmd->next;
	}
	// Parent closes all pipe fds
	ft_close_all_fd(shell);
    // Wait for all children and store exit codes
	wait_child_procs(shell->cmd_list);
	// Write exit code to shell
	ft_write_exit_code(shell);
	// ft_close_all_fd(shell);
	ft_free_cmd_line(shell);
	return (0);
}
