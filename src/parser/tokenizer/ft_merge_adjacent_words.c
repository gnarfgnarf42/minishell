/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_adjacent_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:23:13 by sscholz           #+#    #+#             */
/*   Updated: 2025/04/24 19:23:14 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_join_values(t_shell *shell, const char *a, const char *b)
{
	size_t	len;
	char	*out;

	len = ft_strlen(a) + ft_strlen(b);
	out = ft_track_malloc(shell, len + 1);
	if (!out)
		return (NULL);
	ft_strlcpy(out, a, len + 1);
	ft_strlcat(out, b, len + 1);
	return (out);
}

static void	ft_splice_out_next(t_shell *shell, t_token *cur)
{
	t_token	*to_remove;

	to_remove = cur->next;
	cur->next = to_remove->next;
	ft_track_free(shell, to_remove->value);
	ft_track_free(shell, to_remove);
}

static int	ft_try_merge_pair(t_shell *shell, t_token *cur)
{
	char	*joined;

	if (cur->type != TOKEN_WORD
		|| !cur->next
		|| cur->next->type != TOKEN_WORD
		|| cur->glue == false
		|| cur->next->glue == false
		|| cur->quote_type != cur->next->quote_type)
		return (0);
	joined = ft_join_values(shell, cur->value, cur->next->value);
	if (!joined)
		ft_track_free(shell, cur->value);
	cur->value = joined;
	ft_splice_out_next(shell, cur);
	return (1);
}

void	ft_merge_adjacent_words(t_shell *shell, t_token *head)
{
	t_token	*cur;
	int		res;

	cur = head;
	while (cur && cur->next)
	{
		res = ft_try_merge_pair(shell, cur);
		if (res < 0)
			return ;
		if (res == 1)
			continue ;
		cur = cur->next;
	}
}
