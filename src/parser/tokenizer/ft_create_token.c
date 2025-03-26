/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:54:23 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:54:25 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token_type	ft_set_token_type(const char *value)
{
	if (value[0] == '|' && value[1] == '\0')
		return (TOKEN_PIPE);
	if (value[0] == '<' && value[1] == '\0')
		return (TOKEN_REDIR_IN);
	if (value[0] == '>' && value[1] == '\0')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}

t_token	*ft_create_token(t_shell *shell, t_token_type type,
		const char *value, size_t len)
{
	t_token	*token;

	token = ft_track_malloc(shell, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_track_strndup(shell, value, len);
	if (!token->value)
	{
		ft_track_free(shell, token);
		return (NULL);
	}
	if (type == TOKEN_END)
		token->type = TOKEN_END;
	else
		token->type = ft_set_token_type(value);
	token->next = NULL;
	return (token);
}