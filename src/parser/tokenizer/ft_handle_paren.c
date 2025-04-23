/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_paren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:54:05 by sscholz           #+#    #+#             */
/*   Updated: 2025/04/23 16:54:09 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_handle_paren(t_shell *shell, const char *input, size_t *i)
{
	t_token	*tok;

	if (input[*i] == '(')
		tok = ft_create_token(shell, TOKEN_LPAREN, &input[*i], 1);
	else if (input[*i] == ')')
		tok = ft_create_token(shell, TOKEN_RPAREN, &input[*i], 1);
	else
		return (NULL);
	if (!tok)
		return (NULL);
	(*i)++;
	return (tok);
}
