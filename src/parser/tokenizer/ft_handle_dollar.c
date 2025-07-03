/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:52:09 by sscholz           #+#    #+#             */
/*   Updated: 2025/04/23 19:52:11 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_get_var_name_len(const char *s)
{
	size_t	len;

	len = 0;
	if (s[0] == '?')
		return (1);
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	return (len);
}

t_token	*ft_handle_dollar(t_shell *shell, const char *input, size_t *i)
{
	size_t	name_len;
	char	*name;
	t_token	*token;

	(*i)++;
	name_len = ft_get_var_name_len(&input[*i]);
	name = ft_track_strndup(shell, &input[*i], name_len);
	if (!name)
		return (NULL);
	*i += name_len;
	token = ft_create_token(shell, TOKEN_VAR, name, name_len);
	ft_track_free(shell, name);
	return (token);
}
