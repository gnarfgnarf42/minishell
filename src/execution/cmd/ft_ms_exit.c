/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/19 12:02:44 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_exit(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	// if (write(STDOUT_FILENO, "exit\n", 5) == -1)
	// {
	// 	perror("-minishell");
	// 	cmd->exit_val = 1;
	// 	exit(0);
	// }

	// ft_free_cmd_line(shell, cmd);
	ft_free_all_tracked(shell);
	exit(0);
}
