/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:34:25 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:34:27 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_tokenize_loop(t_shell *shell, const char *input, size_t *i)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_token;

	head = NULL;
	tail = NULL;
	while (input[*i])
	{
		new_token = ft_process_char(shell, input, i);
		if (!new_token && input[*i])
		{
			ft_free_tokens(shell, &head);
			return (NULL);
		}
		if (new_token)
			ft_add_token(&head, &tail, new_token);
		if (!input[*i])
			break ;
	}
	return (head);
}
