/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 12:15:21 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

#define NL		"-n"
#define DELIM	" "

static int	get_nl(t_command *cmd)
{
	if (cmd->argsc > 1 && !ft_strcmp(cmd->args[1], NL))
		return (1);
	return (0);
}

static int	write_args(t_command *cmd, int nl)
{
	int	i;

	i = nl;
	while (++i < cmd->argsc)
	{
		if (write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])) == -1)
		{
			ft_perror("minishell", "echo", strerror(errno));
			cmd->exit_val = 1;
			return (1);
		}
		if (i < cmd->argsc - 1)
		{
			if (write(STDOUT_FILENO, DELIM, 1) == -1)
			{
				ft_perror("minishell", "echo", strerror(errno));
				cmd->exit_val = 1;
				return (1);
			}
		}
	}
	return (0);
}

static int	write_nl(t_command *cmd, int nl)
{
	if (nl == 0)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			ft_perror("minishell", "echo", strerror(errno));
			cmd->exit_val = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_ms_echo(t_shell *shell, t_command *cmd)
{
	int	nl;

	(void)shell;
	nl = get_nl(cmd);
	if (write_args(cmd, nl))
		return (1);
	if (write_nl(cmd, nl))
		return (1);
	cmd->exit_val = 0;
	return (0);
}
