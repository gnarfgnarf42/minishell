/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 16:56:08 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_redir_in(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;
	
	(void)shell;
	(void)cmd;
	token = token->next;
	if (token->type != TOKEN_WORD)
	{
		// Syntax error
		// print error msg
		// set exit_val in cmd 
		return (NULL);
	}
	printf("TOKEN_REDIR_IN: %s\n", token->value);
	// Open file for read and write fd
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		// File open error
		// print error msg
		// set exit_val in cmd 
		return (NULL);
	}
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
	{
		// File close error
		// print error msg
		// set exit_val in cmd 
		return (NULL);
	}
	cmd->fd_in = fd;
	return (token->next);
}
