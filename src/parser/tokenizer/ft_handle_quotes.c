/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:48:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:48:59 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_extract_quoted_string(t_shell *shell, const char *input,
		size_t *i, size_t *len)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	*len = 0;
	while (input[*i + *len] && input[*i + *len] != quote)
		(*len)++;
	if (!input[*i + *len])
		return (NULL);
	return (ft_track_strndup(shell, &input[*i], *len));
}

t_token	*ft_handle_quotes(t_shell *shell, const char *input, size_t *i)
{
	t_token	*token;
	char	*value;
	size_t	len;

	value = ft_extract_quoted_string(shell, input, i, &len);
	if (!value)
		return (NULL);
	token = ft_create_token(shell, TOKEN_WORD, value, len);
	ft_track_free(shell, value);
	if (!token)
		return (NULL);
	*i += len + 1;
	return (token);
}