/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 09:53:25 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_redir_out(t_shell *shell, t_token *token, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	
	token = token->next;
	if (token->type != TOKEN_WORD)
		return (NULL);
	printf("TOKEN_REDIR_OUT: %s\n", token->value);
	// Open file for write and write fd cmd.
	return (token->next);
}