/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 13:54:57 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_append(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;

	(void)shell;
	token = token->next;
	if (token->type != TOKEN_WORD)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
		cmd->exit_val = 2;
		return (NULL);
	}
	fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("-minishell");
		cmd->exit_val = 1;
		return (token->next);
	}
	if (cmd->fd_out != STDOUT_FILENO && close(cmd->fd_out) == -1)
	{
		perror("-minishell");
		cmd->exit_val = 1;
		return (NULL);
	}
	cmd->fd_out = fd;
	return (token->next);
}
