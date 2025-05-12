/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 11:45:56 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_redir_in(t_shell *shell, t_token *token, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	token = token->next;
	if (token->type != TOKEN_WORD)
	{
		// print error msg
		return (NULL);
	}
	printf("TOKEN_REDIR_IN: %s\n", token->value);
	// Open file for read and write fd
	return (token->next);
}