/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 11:35:42 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static int	check_token_type(t_token *token, t_command *cmd)
{
	if (token->type == TOKEN_PIPE || token->type == TOKEN_END)
	{
		ft_perror_syntax(token->value);
		cmd->exit_val = 2;
		return (1);
	}
	return (0);
}

t_token	*ft_process_pipe(t_shell *shell, t_token *token, t_command **cmd)
{
	t_command	*new_cmd;

	(void)shell;
	token = token->next;
	if (check_token_type(token, *cmd))
		return (NULL);
	new_cmd = ft_init_cmd(shell);
	if (new_cmd == NULL)
	{
		ft_perror("minishell", "pipe", strerror(errno), 1);
		(*cmd)->exit_val = 1;
		return (NULL);
	}
	new_cmd->prev = *cmd;
	(*cmd)->next = new_cmd;
	if (pipe((*cmd)->fd_pipe) == -1)
	{
		ft_perror("minishell", "pipe", strerror(errno), 1);
		(*cmd)->exit_val = 1;
		return (NULL);
	}
	*cmd = new_cmd;
	return (token);
}
