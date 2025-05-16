/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:59 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 16:35:50 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static void write_exit_code(t_shell *shell, t_command *cmd_line)
{
	if (!shell || !cmd_line)
		return ;
	while (cmd_line->next)
		cmd_line = cmd_line->next;
	shell->last_exit_status = cmd_line->exit_val;
	return ;
}

int	ft_exec_shell(t_shell *shell)
{
	t_command	*cmd;
	t_command	*cmd_line;

	cmd_line = ft_create_cmd_line(shell);
	if (!cmd_line)
		return (1);
		
	cmd = cmd_line;
	while (cmd)
	{
		if (cmd->exit_val == 0)
			ft_exec_command(shell, cmd);
		write_exit_code(shell, cmd_line);
		ft_close_cmd_fd(cmd);
		cmd = cmd->next;
	}
	ft_free_cmd_line(shell, cmd_line);
	
	return (0);
}