/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_ft_create_ast_node(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	test_assert(stats, node != NULL, "ft_create_ast_node returns non-NULL");
	test_assert(stats, node->type == AST_COMMAND, 
		"ft_create_ast_node sets correct type");
	test_assert(stats, node->args == NULL, 
		"ft_create_ast_node initializes args to NULL");
	test_assert(stats, node->argc == 0, 
		"ft_create_ast_node initializes argc to 0");
	test_assert(stats, node->filename == NULL, 
		"ft_create_ast_node initializes filename to NULL");
	test_assert(stats, node->left == NULL, 
		"ft_create_ast_node initializes left to NULL");
	test_assert(stats, node->right == NULL, 
		"ft_create_ast_node initializes right to NULL");
	test_cleanup_shell(shell);
}

static void	test_ft_create_ast_node_types(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_PIPE);
	test_assert(stats, node->type == AST_PIPE, 
		"ft_create_ast_node creates AST_PIPE");
	node = ft_create_ast_node(shell, AST_REDIR_IN);
	test_assert(stats, node->type == AST_REDIR_IN, 
		"ft_create_ast_node creates AST_REDIR_IN");
	node = ft_create_ast_node(shell, AST_REDIR_OUT);
	test_assert(stats, node->type == AST_REDIR_OUT, 
		"ft_create_ast_node creates AST_REDIR_OUT");
	node = ft_create_ast_node(shell, AST_REDIR_APPEND);
	test_assert(stats, node->type == AST_REDIR_APPEND, 
		"ft_create_ast_node creates AST_REDIR_APPEND");
	node = ft_create_ast_node(shell, AST_REDIR_HEREDOC);
	test_assert(stats, node->type == AST_REDIR_HEREDOC, 
		"ft_create_ast_node creates AST_REDIR_HEREDOC");
	test_cleanup_shell(shell);
}

static void	test_ft_free_ast_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	ft_free_ast(shell, node);
	test_assert(stats, 1, "ft_free_ast handles simple node without crash");
	ft_free_ast(shell, NULL);
	test_assert(stats, 1, "ft_free_ast handles NULL node without crash");
	test_cleanup_shell(shell);
}

static void	test_ft_free_ast_with_args(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 2;
	node->args = ft_track_malloc(shell, sizeof(char *) * 3);
	node->args[0] = ft_track_strdup(shell, "echo");
	node->args[1] = ft_track_strdup(shell, "hello");
	node->args[2] = NULL;
	ft_free_ast(shell, node);
	test_assert(stats, 1, "ft_free_ast handles node with args without crash");
	test_cleanup_shell(shell);
}

static void	test_ft_free_ast_with_filename(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_REDIR_OUT);
	node->filename = ft_track_strdup(shell, "output.txt");
	ft_free_ast(shell, node);
	test_assert(stats, 1, 
		"ft_free_ast handles node with filename without crash");
	test_cleanup_shell(shell);
}

static void	test_ft_free_ast_recursive(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*root;
	t_ast_node	*left;
	t_ast_node	*right;

	shell = test_create_shell();
	root = ft_create_ast_node(shell, AST_PIPE);
	left = ft_create_ast_node(shell, AST_COMMAND);
	right = ft_create_ast_node(shell, AST_COMMAND);
	root->left = left;
	root->right = right;
	ft_free_ast(shell, root);
	test_assert(stats, 1, "ft_free_ast handles recursive tree without crash");
	test_cleanup_shell(shell);
}

void	test_ast_creation(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Creation Functions ===\n");
	test_ft_create_ast_node(&stats);
	test_ft_create_ast_node_types(&stats);
	test_ft_free_ast_simple(&stats);
	test_ft_free_ast_with_args(&stats);
	test_ft_free_ast_with_filename(&stats);
	test_ft_free_ast_recursive(&stats);
	test_summary(&stats, "AST Creation");
}