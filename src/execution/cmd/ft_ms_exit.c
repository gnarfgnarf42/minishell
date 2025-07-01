/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 22:35:28 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static int	is_not_numeric(char	*arg)
{
	if (!arg)
		return (1);
	if (*arg == 0)
		return (2);
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (2);
		arg++;
	}
	return (0);
}

static int	perror_exit(char *arg, char *msg, int code)
{
	ft_putstr_fd("-minishell: exit: ", STDERR_FILENO);
	if (*arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return ((unsigned char)code);
}

int	ft_ms_exit(t_shell *shell, t_command *cmd)
{
	int code;

	if (cmd->argsc == 1)
    	code = shell->last_exit_status;
	else if (cmd->argsc > 2)
		code = perror_exit("", "too many arguments", 1);
	else if (cmd->argsc == 2)
	{
		if (is_not_numeric(cmd->args[1]))
			code = perror_exit(cmd->args[1], "numeric argument required", 2);
		else
			code = ft_atoi(cmd->args[1]);
	}
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
	cmd->exit_val = code & 0xFF;
	shell->exit = 0;
	return (cmd->exit_val);
}
