/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:38:34 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 20:38:35 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*ft_process_char(t_shell *shell, const char *input, size_t *i)
{
	ft_skip_whitespace(input, i);
	if (!input[*i])
		return (NULL);
	if (input[*i + 1] && ft_is_multichar_start(input[*i], input[*i + 1]))
		return (ft_handle_multichar_op(shell, input, i));
	if (input[*i] == '(' || input[*i] == ')')
		return (ft_handle_paren(shell, input, i));
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (ft_handle_operator(shell, input, i));
	else
		return (ft_handle_word(shell, input, i));
}
