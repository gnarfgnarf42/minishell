/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 01:28:28 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token	*ft_process_redir_in(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;

	(void)shell;
	token = token->next;
	if (token->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
		cmd->exit_val = 2;
		return (NULL);
	}
	if (access(token->value, F_OK) == -1)
	{
		
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		// ft_putstr_fd(token->value, STDERR_FILENO);
		perror(token->value);
		cmd->exit_val = 1;
		return (token->next);	
	}
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(token->value);
		cmd->exit_val = 1;
		return (token->next);
	}
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror("minishell: ");
		cmd->exit_val = 1;
		close(fd);
		return (NULL);
	}
	cmd->fd_in = fd;
	return (token->next);
}
