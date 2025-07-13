/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_count_args(t_token *start, t_token *end)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
	}
	return (count);
}

static char	**ft_alloc_args(t_shell *shell, int count)
{
	char	**args;

	if (count == 0)
		return (NULL);
	args = ft_track_malloc(shell, sizeof(char *) * (count + 1));
	return (args);
}

static char	**ft_extract_args(t_shell *shell, t_token *start, t_token *end)
{
	char	**args;
	int		count;
	int		i;
	t_token	*current;

	count = ft_count_args(start, end);
	args = ft_alloc_args(shell, count);
	if (!args)
		return (NULL);
	i = 0;
	current = start;
	while (current && current != end && i < count)
	{
		if (current->type == TOKEN_WORD)
		{
			args[i] = ft_track_strdup(shell, current->value);
			if (!args[i])
				return (NULL);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static t_token	*ft_find_cmd_end(t_token *start)
{
	t_token	*end;

	end = start;
	while (end && end->type == TOKEN_WORD)
		end = end->next;
	return (end);
}

t_ast_node	*ft_parse_command(t_shell *shell, t_token **current)
{
	t_ast_node	*cmd_node;
	t_token		*start;
	t_token		*end;

	if (!*current || (*current)->type != TOKEN_WORD)
		return (NULL);
	cmd_node = ft_create_ast_node(shell, AST_COMMAND);
	if (!cmd_node)
		return (NULL);
	start = *current;
	end = ft_find_cmd_end(start);
	cmd_node->argc = ft_count_args(start, end);
	cmd_node->args = ft_extract_args(shell, start, end);
	if (!cmd_node->args && cmd_node->argc > 0)
		return (NULL);
	*current = end;
	return (cmd_node);
}
