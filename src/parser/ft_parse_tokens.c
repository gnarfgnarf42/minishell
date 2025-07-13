/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*ft_skip_parens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && (current->type == TOKEN_LPAREN
			|| current->type == TOKEN_RPAREN))
		current = current->next;
	return (current);
}

t_ast_node	*ft_parse_tokens(t_shell *shell, t_token *tokens)
{
	t_token		*current;
	t_ast_node	*ast;

	if (!tokens)
		return (NULL);
	current = ft_skip_parens(tokens);
	if (!current || current->type == TOKEN_END)
		return (NULL);
	ast = ft_parse_pipeline(shell, &current);
	if (!ast)
		return (NULL);
	return (ast);
}
