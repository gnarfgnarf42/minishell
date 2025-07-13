/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_type	ft_get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (AST_REDIR_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (AST_REDIR_OUT);
	else if (type == TOKEN_REDIR_APPEND)
		return (AST_REDIR_APPEND);
	else
		return (AST_REDIR_HEREDOC);
}

static int	ft_is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

t_ast_node	*ft_parse_redirections(t_shell *shell, t_token **current,
			t_ast_node *cmd)
{
	t_ast_node	*redir_node;
	t_ast_type	redir_type;

	while (*current && ft_is_redir_token((*current)->type))
	{
		redir_type = ft_get_redir_type((*current)->type);
		redir_node = ft_create_ast_node(shell, redir_type);
		if (!redir_node)
			return (NULL);
		*current = (*current)->next;
		if (!*current || (*current)->type != TOKEN_WORD)
			return (NULL);
		redir_node->filename = ft_track_strdup(shell, (*current)->value);
		if (!redir_node->filename)
			return (NULL);
		redir_node->left = cmd;
		cmd = redir_node;
		*current = (*current)->next;
	}
	return (cmd);
}

static t_ast_node	*ft_create_pipe_node(t_shell *shell, t_ast_node *left,
					t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = ft_create_ast_node(shell, AST_PIPE);
	if (!pipe_node)
		return (NULL);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*ft_parse_pipeline(t_shell *shell, t_token **current)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = ft_parse_command(shell, current);
	if (!left)
		return (NULL);
	left = ft_parse_redirections(shell, current, left);
	if (!left)
		return (NULL);
	while (*current && (*current)->type == TOKEN_PIPE)
	{
		*current = (*current)->next;
		right = ft_parse_command(shell, current);
		if (!right)
			return (NULL);
		right = ft_parse_redirections(shell, current, right);
		if (!right)
			return (NULL);
		left = ft_create_pipe_node(shell, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}
