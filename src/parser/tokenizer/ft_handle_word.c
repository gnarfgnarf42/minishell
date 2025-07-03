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

static int	ft_is_word_boundary(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == '|' || c == '<' || c == '>' || c == '('
		|| c == ')' || c == '\0');
}

static char	*ft_handle_double_quotes(t_shell *shell, const char *input,
		size_t *i, char *result);

static char	*ft_handle_quotes_in_word(t_shell *shell, const char *input,
		size_t *i, char *result)
{
	char	*content;
	char	quote_char;

	quote_char = input[*i];
	if (quote_char == '\'')
	{
		content = ft_process_quoted_content(shell, input, i, quote_char);
		if (!content)
			return (NULL);
		result = ft_append_to_result(shell, result, content);
		ft_track_free(shell, content);
	}
	else
	{
		result = ft_handle_double_quotes(shell, input, i, result);
	}
	return (result);
}

static char	*ft_handle_double_quotes(t_shell *shell, const char *input,
		size_t *i, char *result)
{
	size_t	start;
	char	*expanded;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			if (*i > start)
			{
				expanded = ft_track_strndup(shell, &input[start], *i - start);
				result = ft_append_to_result(shell, result, expanded);
				ft_track_free(shell, expanded);
			}
			expanded = ft_expand_variable(shell, input, i);
			result = ft_append_to_result(shell, result, expanded);
			ft_track_free(shell, expanded);
			start = *i;
		}
		else
			(*i)++;
	}
	if (!input[*i])
		return (NULL);
	if (*i > start)
	{
		expanded = ft_track_strndup(shell, &input[start], *i - start);
		result = ft_append_to_result(shell, result, expanded);
		ft_track_free(shell, expanded);
	}
	(*i)++;
	return (result);
}

static char	*ft_process_word_part(t_shell *shell, const char *input,
		size_t *i, char *current_result, int *was_quoted)
{
	char	*temp;
	char	*result;

	result = current_result;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		*was_quoted = 1;
		result = ft_handle_quotes_in_word(shell, input, i, result);
	}
	else if (input[*i] == '$')
	{
		temp = ft_expand_variable(shell, input, i);
		result = ft_append_to_result(shell, result, temp);
		ft_track_free(shell, temp);
	}
	else
	{
		temp = ft_process_regular_text(shell, input, i);
		result = ft_append_to_result(shell, result, temp);
		ft_track_free(shell, temp);
	}
	return (result);
}

static char	*ft_build_complex_word(t_shell *shell, const char *input,
		size_t *i, int *was_quoted)
{
	char	*result;

	result = ft_track_strdup(shell, "");
	if (!result)
		return (NULL);
	while (input[*i] && !ft_is_word_boundary(input[*i]))
	{
		result = ft_process_word_part(shell, input, i, result, was_quoted);
		if (!result)
			return (NULL);
	}
	return (result);
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
			return (TOKEN_SKIP);
	}
	token = ft_create_token(shell, TOKEN_WORD, word_value,
			ft_strlen(word_value));
	ft_track_free(shell, word_value);
	return (token);
}
