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

static void	ft_quote_error(int in_single, int in_double)
{
	if (in_single)
		write(STDERR_FILENO,
			"minishell: syntax error: unclosed single quote\n", 48);
	if (in_double)
		write(STDERR_FILENO, "minishell: syntax error: unclosed quote\n", 40);
}

static int	ft_validate_quotes(const char *input)
{
	size_t	i;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote || in_double_quote)
	{
		ft_quote_error(in_single_quote, in_double_quote);
		return (0);
	}
	return (1);
}

t_token	*ft_tokenize(t_shell *shell, const char *input)
{
	t_token	*head;
	size_t	i;

	if (!ft_validate_quotes(input))
		return (NULL);
	i = 0;
	head = ft_tokenize_loop(shell, input, &i);
	if (head)
		head = ft_finalize_tokens(shell, head);
	return (head);
}
