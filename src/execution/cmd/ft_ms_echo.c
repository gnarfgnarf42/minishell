/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 16:17:41 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_echo(t_shell *shell, t_command *cmd)
{
	bool	nl;
	int		i;

	(void)shell;
	nl = 1;
	i = 0;
	if (cmd->argsc > 1 && !ft_strcmp(cmd->args[1], "-n"))
	{
		nl = 0;
		i++;
	}
	while (++i < cmd->argsc)
	{
		if (write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])) == -1)
		{
			perror("-minishell");
			cmd->exit_val = 1;
			return (-1);
		}
		if (i < cmd->argsc - 1)
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("-minishell");
				cmd->exit_val = 1;
				return (-1);
			}
		}
	if (nl)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("-minishell");
			cmd->exit_val = 1;
			return (-1);
		}
	cmd->exit_val = 0;
	return (0);
}
