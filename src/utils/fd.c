/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:59:29 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 00:10:05 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_close_cmd_fd(t_command *cmd)
{
	if (cmd->next)
	{
		close(cmd->fd_pipe[0]);
		close(cmd->fd_pipe[1]);
	}
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	return (0);
}

int	ft_close_all_fd(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->cmd_list;
	while (cmd)
	{
		ft_close_cmd_fd(cmd);
		cmd = cmd->next;
	}
	return (0);
}

void	ft_dup_fd(t_command *cmd)
{
	if (cmd->next && cmd->fd_pipe[1] != STDOUT_FILENO)
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
	if (cmd->prev && cmd->prev->fd_pipe[0] != STDIN_FILENO)
		dup2(cmd->prev->fd_pipe[0], STDIN_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
}
