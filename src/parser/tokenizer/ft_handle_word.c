/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:46:13 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:46:15 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_get_word_length(const char *input, size_t i)
{
	size_t	len;

	len = 0;
	while (input[i + len] && input[i + len] != ' ' && input[i + len] != '|'
		&& input[i + len] != '<' && input[i + len] != '>'
		&& input[i + len] != '"' && input[i + len] != '\''
		&& input[i + len] != '$')
		len++;
	return (len);
}

t_token	*ft_handle_word(t_shell *shell, const char *input, size_t *i)
{
	t_token	*token;
	size_t	len;

	len = ft_get_word_length(input, *i);
	token = ft_create_token(shell, TOKEN_WORD, &input[*i], len);
	token->glue = false;
	token->quote_type = QUOTE_NONE;
	if (!token)
		return (NULL);
	*i += len;
	return (token);
}
