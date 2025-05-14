/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/13 18:08:11 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_redir_in(t_shell *shell, t_token *token, t_command *cmd)
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
	// printf("TOKEN_REDIR_IN: %s\n", token->value);
	// Open file for read
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		// File open error
		perror("-minishell");
		cmd->exit_val = 1; 
		return (NULL);
	}
	// Closing previous redirection in
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
	{
		// File close error
		perror("-minishell");
		cmd->exit_val = 1; 
		return (NULL);
	}
	// Change fd_in in cmd
	cmd->fd_in = fd;
	return (token->next);
}
