/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:35:48 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 19:38:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static void	print_tokens_bonus(t_token *cur);

void	ft_print_tokens(t_token *cur)
{
	while (cur)
	{
		printf("Token type: %d   ", cur->type);
		if (cur->type == TOKEN_VAR)
			printf("VAR: ");
		else if (cur->type == TOKEN_WORD)
			printf("WORD: ");
		else if (cur->type == TOKEN_PIPE)
			printf("PIPE: ");
		else if (cur->type == TOKEN_REDIR_IN)
			printf("REDIR_IN: ");
		else if (cur->type == TOKEN_REDIR_OUT)
			printf("REDIR_OUT: ");
		else if (cur->type == TOKEN_REDIR_HEREDOC)
			printf("HEREDOC: ");
		else if (cur->type == TOKEN_REDIR_APPEND)
			printf("APPEND: ");
		else
			print_tokens_bonus(cur);
		printf("\"%s\"\n", cur->value);
		cur = cur->next;
	}
}

static void	print_tokens_bonus(t_token *cur)
{
	if (cur->type == TOKEN_AND)
		printf("AND: ");
	else if (cur->type == TOKEN_OR)
		printf("OR: ");
	else if (cur->type == TOKEN_LPAREN)
		printf("LPAREN: ");
	else if (cur->type == TOKEN_RPAREN)
		printf("RPAREN: ");
	else if (cur->type == TOKEN_END)
		printf("END: ");
	else
		printf("UNKNOWN: ");
}
