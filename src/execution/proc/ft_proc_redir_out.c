/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/15 15:03:01 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_redir_out(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;
	
	(void)shell;
	token = token->next;
	// Check for syntax errors
	if (token->type != TOKEN_WORD)
	{
		// Syntax error
		write(STDERR_FILENO, "-minishell: syntax error near unexpected token\n", 47);
		cmd->exit_val = 2;  
		return (NULL);
	}
	// printf("TOKEN_REDIR_OUT: %s\n", token->value);
	// Open or create file for append
	fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		// File open error
		perror("-minishell");
		cmd->exit_val = 1; 
		return (NULL);
	}
	// Closing previous redirection out fd
	if (cmd->fd_out != STDOUT_FILENO && close(cmd->fd_out) == -1)
	{
		// File close error
		perror("-minishell");
		cmd->exit_val = 1; 
		return (NULL);
	}
	// Change fd_in in cmd
	cmd->fd_out = fd;
	return (token->next);
}
