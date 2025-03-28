/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finalize_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:35:39 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:35:40 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_finalize_tokens(t_shell *shell, t_token *head)
{
	t_token	*end;
	t_token	*tail;

	end = ft_create_token(shell, TOKEN_END, "", 0);
	if (!end)
	{
		ft_free_tokens(shell, &head);
		return (NULL);
	}
	tail = head;
	while (tail && tail->next)
		tail = tail->next;
	ft_add_token(&head, &tail, end);
	return (head);
}
