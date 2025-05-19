/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:04:27 by sscholz           #+#    #+#             */
/*   Updated: 2025/05/16 14:47:33 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	ft_expand_var_node(t_shell *shell, t_token *tok)
{
	char	*lookup;
	char	*env;

	if (tok->value[0] == '?' && tok->value[1] == '\0')
	{
		lookup = ft_itoa(shell->last_exit_status);
		if (!lookup)
			return (0);
	}
	else
	{
		// env = getenv(tok->value);
		env = ft_getenv(shell, tok->value);
		if (env)
			lookup = ft_track_strdup(shell, env);
		else
			lookup = ft_track_strdup(shell, "");
		if (!lookup)
			return (0);
	}
	ft_track_free(shell, tok->value);
	tok->value = lookup;
	tok->type = TOKEN_WORD;
	return (1);
}

static int	ft_expand_all_vars(t_shell *shell, t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type == TOKEN_VAR)
			if (!ft_expand_var_node(shell, cur))
				return (0);
		cur = cur->next;
	}
	return (1);
}

t_token	*ft_expand_vars(t_shell *shell, t_token *head)
{
	if (!ft_expand_all_vars(shell, head))
	{
		ft_free_tokens(shell, &head);
		return (NULL);
	}
	ft_merge_adjacent_words(shell, head);
	return (head);
}
