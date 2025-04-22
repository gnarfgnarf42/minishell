/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:17 by nefimov           #+#    #+#             */
/*   Updated: 2025/04/22 18:00:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void ft_exec_command(t_command *cmd)
{
	pid_t	pid;
	int		status;
	// int		ex_status;

	cmd->exit_val = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		cmd->exit_val = 1;
		// ex_status = 1;
		//return (1);
	}
	if (pid == 0)
	{
		execve(cmd->pathname, cmd->args, cmd->envp);
		perror("execve failed");
		cmd->exit_val = 127;
		exit(127);
		// ex_status = 127;
		// return (127);
	}
	else
	{
		printf("pid: %d\n", pid);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && cmd->exit_val != 127)
		{
			printf("Exit code: %d\n", WEXITSTATUS(status));
			cmd->exit_val = WEXITSTATUS(status);
			//return (WEXITSTATUS(status));
		}
		else
		{
			printf("Child process did not terminate normally.\n");
			cmd->exit_val = 127;
			// return (127);
		}
		// return (ex_status);
	}
	// printf("Return: %d\n", ex_status);
	// return (ex_status);
}
