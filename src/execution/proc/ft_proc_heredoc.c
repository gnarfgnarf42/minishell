/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 09:54:31 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_heredoc(t_shell *shell, t_token *token, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	
	token = token->next;
	if (token->type != TOKEN_WORD)
		return (NULL);
	printf("TOKEN_HEREDOC: %s\n", token->value);
	// Code to process HereDoc
	return (token->next);
}