/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/15 15:08:09 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_env(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	
	if (write(STDOUT_FILENO, "env\n", 4) == -1)
	{
		perror("-minishell");
		cmd->exit_val = 1;
		return (-1);
	}
	return (0);
}