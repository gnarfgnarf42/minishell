/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_word_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:46:13 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/03 15:30:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_process_word_part(t_shell *shell, const char *input,
		size_t *i, char *current_result)
{
	char	*temp;
	char	*result;

	result = current_result;
	if (input[*i] == '"' || input[*i] == '\'')
	{
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

char	*ft_build_complex_word(t_shell *shell, const char *input,
		size_t *i, int *was_quoted)
{
	char	*result;

	result = ft_track_strdup(shell, "");
	if (!result)
		return (NULL);
	while (input[*i] && !ft_is_word_boundary(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
			*was_quoted = 1;
		result = ft_process_word_part(shell, input, i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}
