/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 18:41:35 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token	*ft_process_pipe(t_shell *shell, t_token *token, t_command **cmd)
{
	t_command	*new_cmd;

	(void)shell;
	token = token->next;
	if (token->type == TOKEN_PIPE || token->type == TOKEN_END)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
		(*cmd)->exit_val = 2;
		return (NULL);
	}

	new_cmd = ft_init_cmd(shell);
	if (new_cmd == NULL)
	{
		perror("-minishell");
		(*cmd)->exit_val = 1;
		return (NULL);
	}
	new_cmd->prev = *cmd;
	(*cmd)->next = new_cmd;
	if (pipe((*cmd)->fd_pipe) == -1)
	{
		perror("-minishell");
		(*cmd)->exit_val = 1;
		return (NULL);
	}
	*cmd = new_cmd;
	return (token);
}
