/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:30:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/03 15:30:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_get_var_value(t_shell *shell, const char *var_name)
{
	char	*env_value;
	char	*result;

	if (!var_name)
		return (ft_track_strdup(shell, ""));
	if (var_name[0] == '?' && var_name[1] == '\0')
		return (ft_itoa(shell->last_exit_status));
	env_value = getenv(var_name);
	if (env_value)
		result = ft_track_strdup(shell, env_value);
	else
		result = ft_track_strdup(shell, "");
	return (result);
}

char	*ft_expand_variable(t_shell *shell, const char *input, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*var_value;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'
			|| (start == *i && input[*i] == '?')))
	{
		(*i)++;
		if (input[*i - 1] == '?')
			break ;
	}
	len = *i - start;
	if (len == 0)
		return (ft_track_strdup(shell, "$"));
	var_name = ft_track_strndup(shell, &input[start], len);
	if (!var_name)
		return (NULL);
	var_value = ft_get_var_value(shell, var_name);
	ft_track_free(shell, var_name);
	return (var_value);
}

char	*ft_append_to_result(t_shell *shell, char *result, const char *append)
{
	char	*old_result;
	char	*new_result;

	if (!append)
		return (result);
	old_result = result;
	new_result = ft_track_strjoin(shell, old_result, append);
	ft_track_free(shell, old_result);
	return (new_result);
}

char	*ft_process_quoted_content(t_shell *shell, const char *input,
		size_t *i, char quote_char)
{
	size_t	start;
	size_t	len;
	char	*content;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (!input[*i])
		return (NULL);
	len = *i - start;
	content = ft_track_strndup(shell, &input[start], len);
	(*i)++;
	return (content);
}

char	*ft_process_regular_text(t_shell *shell, const char *input, size_t *i)
{
	size_t	start;
	size_t	len;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '\n' && input[*i] != '\r' && input[*i] != '\v'
		&& input[*i] != '\f' && input[*i] != '|' && input[*i] != '<'
		&& input[*i] != '>' && input[*i] != '(' && input[*i] != ')'
		&& input[*i] != '"' && input[*i] != '\'' && input[*i] != '$')
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_track_strdup(shell, ""));
	return (ft_track_strndup(shell, &input[start], len));
}