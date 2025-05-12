/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 09:52:26 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token		*ft_process_pipe(t_shell *shell, t_token *token, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	
	token = token->next;
	if (token->type == TOKEN_PIPE || token->type == TOKEN_END)
		return (NULL);
	printf("TOKEN_PIPE: %s\n", token->value);
	// Create pipe, redirect fd's, create new cmd, redirect fd's
	return (token->next);
}