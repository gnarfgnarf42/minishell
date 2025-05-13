/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/13 15:01:10 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_pipe(t_shell *shell, t_token *token, t_command **cmd)
{
	t_command	*new_cmd;
	(void)shell;
	(void)cmd;
	
	token = token->next;
	if (token->type == TOKEN_PIPE || token->type == TOKEN_END)
	{
		write(STDERR_FILENO, "-minishell: syntax error near unexpected token\n", 47);
		(*cmd)->exit_val = 2;  
		return (NULL);
	}
	printf("TOKEN_PIPE: %s\n", token->value);
	// Create new cmd
	new_cmd = ft_init_cmd(shell);
	new_cmd->prev = *cmd;
	(*cmd)->next = new_cmd;
	// Create pipe
	if (pipe((*cmd)->fd_pipe) == -1)
	{
		perror("-minishell");
		(*cmd)->exit_val = 1;
		return (NULL);
	}
	// if ((*cmd)->prev == NULL)
	// 	if (close((*cmd)->fd_pipe[0] == -1))
	// 	{
	// 		perror("-minishell");
	// 		(*cmd)->exit_val = 1;
	// 		return (NULL);
	// 	}
	*cmd = new_cmd;
	return (token);
}
