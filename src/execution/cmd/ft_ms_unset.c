/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/15 15:08:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_unset(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	
	if (write(STDOUT_FILENO, "unset\n", 6) == -1)
	{
		perror("-minishell");
		cmd->exit_val = 1;
		return (-1);
	}
	return (0);
}