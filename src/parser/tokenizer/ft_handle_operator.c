/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:49:31 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:49:32 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*ft_handle_operator(t_shell *shell, const char *input, size_t *i)
{
	t_token	*token;

	if (!ft_is_operator(input[*i]))
		return (NULL);
	if (input[*i] == '|')
		token = ft_create_token(shell, TOKEN_PIPE, &input[*i], 1);
	else if (input[*i] == '<')
		token = ft_create_token(shell, TOKEN_REDIR_IN, &input[*i], 1);
	else
		token = ft_create_token(shell, TOKEN_REDIR_OUT, &input[*i], 1);
	if (!token)
		return (NULL);
	(*i)++;
	return (token);
}
