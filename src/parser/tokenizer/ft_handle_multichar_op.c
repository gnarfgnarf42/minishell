/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_multichar_op.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:59:30 by sscholz           #+#    #+#             */
/*   Updated: 2025/04/23 15:59:31 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_multichar_start(char c, char next)
{
	return ((c == '<' && next == '<')
		|| (c == '>' && next == '>')
		|| (c == '&' && next == '&')
		|| (c == '|' && next == '|'));
}

t_token	*ft_handle_multichar_op(t_shell *shell, const char *input, size_t *i)
{
	t_token	*token;

	if (!ft_is_multichar_start(input[*i], input[*i + 1]))
		return (NULL);
	if (input[*i] == '<')
		token = ft_create_token(shell, TOKEN_REDIR_HEREDOC, &input[*i], 2);
	else if (input[*i] == '>')
		token = ft_create_token(shell, TOKEN_REDIR_APPEND, &input[*i], 2);
	else if (input[*i] == '&')
		token = ft_create_token(shell, TOKEN_AND, &input[*i], 2);
	else
		token = ft_create_token(shell, TOKEN_OR, &input[*i], 2);
	if (!token)
		return (NULL);
	*i += 2;
	return (token);
}
