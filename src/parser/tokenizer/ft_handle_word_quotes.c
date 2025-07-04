/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_word_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:46:13 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/03 15:30:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_add_text_segment(t_shell *shell, const char *text,
			size_t len, char *result)
{
	char	*expanded;

	if (len > 0)
	{
		expanded = ft_track_strndup(shell, text, len);
		result = ft_append_to_result(shell, result, expanded);
		ft_track_free(shell, expanded);
	}
	return (result);
}

static char	*ft_process_dollar_in_quotes(t_shell *shell, const char *input,
			size_t *i, char *result)
{
	char	*expanded;

	expanded = ft_expand_variable(shell, input, i);
	result = ft_append_to_result(shell, result, expanded);
	ft_track_free(shell, expanded);
	return (result);
}

static char	*ft_handle_double_quotes_content(t_shell *shell, const char *input,
			size_t *i, char *result)
{
	size_t	start;

	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			result = ft_add_text_segment(shell, &input[start],
					*i - start, result);
			result = ft_process_dollar_in_quotes(shell, input, i, result);
			start = *i;
		}
		else
			(*i)++;
	}
	result = ft_add_text_segment(shell, &input[start], *i - start, result);
	return (result);
}

char	*ft_handle_double_quotes(t_shell *shell, const char *input,
		size_t *i, char *result)
{
	(*i)++;
	result = ft_handle_double_quotes_content(shell, input, i, result);
	if (!input[*i])
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 40);
		return (NULL);
	}
	(*i)++;
	return (result);
}

char	*ft_handle_quotes_in_word(t_shell *shell, const char *input,
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
