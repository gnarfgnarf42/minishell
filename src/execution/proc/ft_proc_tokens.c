/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 18:49:26 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Check type of the Token and process it
// Return a pointer to the next token to process
t_token	*ft_process_token(t_shell *shell, t_token *token, t_command **cmd)
{
	(void)shell;
	if (token->type == TOKEN_WORD)
		return (ft_process_word(shell, token, *cmd));
	else if (token->type == TOKEN_REDIR_IN)
		return (ft_process_redir_in(shell, token, *cmd));
	else if (token->type == TOKEN_REDIR_OUT)
		return (ft_process_redir_out(shell, token, *cmd));
	else if (token->type == TOKEN_APPEND)
		return (ft_process_append(shell, token, *cmd));
	else if (token->type == TOKEN_HEREDOC)
		return (ft_process_heredoc(shell, token, *cmd));
	else if (token->type == TOKEN_PIPE)
		return (ft_process_pipe(shell, token, cmd));
	else
		token = token->next;
	return (token);
}

// Read tokens from shell and create commands for execution
t_command	*ft_create_cmd_line(t_shell *shell)
{
	t_token		*cur_token;
	t_token		*next_token;
	t_command	*cmd_line;
	t_command	*cmd;

	cmd = ft_init_cmd(shell);
	if (cmd == NULL)
		return (NULL);
	cmd_line = cmd;
	cur_token = shell->tokens;
	while (cur_token && cur_token->type != TOKEN_END)
	{
		next_token = ft_process_token(shell, cur_token, &cmd);
		if (next_token == NULL && cmd->exit_val == 0)
			cmd->exit_val = 22;
		cur_token = next_token;
	}
	return (cmd_line);
}
