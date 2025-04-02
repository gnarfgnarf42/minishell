/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:24:50 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:24:52 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_tokenize(t_shell *shell, const char *input)
{
	t_token	*head;
	size_t	i;

	head = NULL;
	i = 0;
	head = ft_tokenize_loop(shell, input, &i);
	if (!head && input[i])
		return (NULL);
	return (ft_finalize_tokens(shell, head));
}
