/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/07 19:05:40 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Check type of the Token and process it
// Return a pointer to the next token to process
t_token		*ft_process_token(t_shell *shell, t_token *token, t_command *cmd)
{
	// TOKEN_WORD
	// Add a new argument to args and cmdname if it is NULL.
	(void)shell;
	if (token->type == TOKEN_WORD)
	{
		if (cmd->cmdname == NULL)
			cmd->cmdname = token->value;
		cmd->args[cmd->argsc++] = token->value;
		printf("TOKEN_WORD: %s\n", token->value);
		return (token++);	
	}
	// TOKEN_REDIR_IN
	else if (token->type == TOKEN_REDIR_IN)
	{
		token = token->next;
		if (token->type != TOKEN_WORD)
			return (NULL);
		printf("TOKEN_REDIR_IN: %s\n", token->value);
		// Open file for read and write fd
	}
	// else if (token->type == TOKEN_REDIR_OUT)
	// else if (token->type == TOKEN_APPEND)
	// else if (token->type == TOKEN_HEREDOC)
	// else if (token->type == TOKEN_PIPE)
	else
		token = token->next;
	return (token);
}

t_command	*ft_create_exec_line(t_shell *shell)
{
	t_token		*cur_token;
	t_token		*next_token;
	t_command	*cmd_line;
	t_command	*cmd;
	// int			err;

	cmd = init_cmd(shell);
	if (cmd == NULL)
		return (NULL);
	cmd_line = cmd;
	cur_token = shell->tokens;
	// err = 0;
	while (cur_token && cur_token->type != TOKEN_END)
	{
		next_token = ft_process_token(shell, cur_token, cmd);
		if (next_token == NULL && cmd->exit_val == 0)
			cmd->exit_val = 2;
		// else if (cmd_line == NULL)
		// cmd_line = cmd;
		cur_token = next_token;
	}
	return (cmd_line);
}
