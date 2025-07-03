/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:46:13 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/03 15:30:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_word_boundary(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == '|' || c == '<' || c == '>' || c == '('
		|| c == ')' || c == '\0');
}

t_token	*ft_handle_word(t_shell *shell, const char *input, size_t *i)
{
	char	*word_value;
	t_token	*token;
	int		was_quoted;

	was_quoted = 0;
	word_value = ft_build_complex_word(shell, input, i, &was_quoted);
	if (!word_value)
		return (NULL);
	if (ft_strlen(word_value) == 0)
	{
		ft_track_free(shell, word_value);
		if (was_quoted)
			return (ft_create_token(shell, TOKEN_WORD, "", 0));
		else
			return ((t_token *)TOKEN_SKIP);
	}
	token = ft_create_token(shell, TOKEN_WORD, word_value,
			ft_strlen(word_value));
	ft_track_free(shell, word_value);
	return (token);
}
