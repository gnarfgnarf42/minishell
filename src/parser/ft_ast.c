/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*ft_create_ast_node(t_shell *shell, t_ast_type type)
{
	t_ast_node	*node;

	node = ft_track_malloc(shell, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->argc = 0;
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void	ft_free_ast_args(t_shell *shell, t_ast_node *node)
{
	int	i;

	if (!node->args)
		return ;
	i = 0;
	while (i < node->argc)
	{
		ft_track_free(shell, node->args[i]);
		i++;
	}
	ft_track_free(shell, node->args);
}

void	ft_free_ast(t_shell *shell, t_ast_node *node)
{
	if (!node)
		return ;
	ft_free_ast_args(shell, node);
	if (node->filename)
		ft_track_free(shell, node->filename);
	ft_free_ast(shell, node->left);
	ft_free_ast(shell, node->right);
	ft_track_free(shell, node);
}
