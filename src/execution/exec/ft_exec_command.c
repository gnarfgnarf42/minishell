/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:17 by nefimov           #+#    #+#             */
/*   Updated: 2025/04/23 17:14:53 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void ft_exec_command(t_command *cmd)
{
	pid_t	pid;

	cmd->exit_val = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd->pathname, cmd->args, cmd->envp);
		perror("execve failed");
		cmd->exit_val = 127;
		exit(127);
	}
	else
	{
		cmd->exit_val = get_exit_code(pid);
		printf("Exit code: %d\n", cmd->exit_val);
	}
}
