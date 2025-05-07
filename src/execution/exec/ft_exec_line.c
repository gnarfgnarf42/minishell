/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/07 12:16:50 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_token(t_shell *shell, t_token *token, t_command *cmd)
{
	if (token->type == TOKEN_WORD)
	{
		if (cmd == NULL)
		{
			cmd = init_cmd(shell, token->value);
		}
	}			
	// else if (token->type == TOKEN_REDIR_IN)
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
	t_command	*cmd_line;
	t_command	*cmd;
	int			err;

	cmd = NULL;
	cmd_line = NULL;
	cur_token = shell->tokens;
	err = 0;
	while (cur_token && cur_token->type != TOKEN_END)
	{
		cur_token = ft_process_token(shell, cur_token, cmd);
		if (cur_token = NULL)
			cmd->exit_val = 2;
		else if (cmd_line == NULL)
			cmd_line = cur_token;
	}
}
