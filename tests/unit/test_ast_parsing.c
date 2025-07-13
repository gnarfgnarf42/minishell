/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_ft_parse_command_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*node;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	current = tokens;
	node = ft_parse_command(shell, &current);
	test_assert(stats, node != NULL, "ft_parse_command returns non-NULL");
	test_assert(stats, node->type == AST_COMMAND, 
		"ft_parse_command creates AST_COMMAND");
	test_assert(stats, node->argc == 1, 
		"ft_parse_command sets correct argc");
	test_assert(stats, strcmp(node->args[0], "echo") == 0, 
		"ft_parse_command sets correct args[0]");
	test_assert(stats, current == NULL, 
		"ft_parse_command advances current pointer");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_command_with_args(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*node;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next = test_create_token(shell, TOKEN_WORD, "hello");
	tokens->next->next = test_create_token(shell, TOKEN_WORD, "world");
	current = tokens;
	node = ft_parse_command(shell, &current);
	test_assert(stats, node != NULL, 
		"ft_parse_command with args returns non-NULL");
	test_assert(stats, node->argc == 3, 
		"ft_parse_command with args sets correct argc");
	test_assert(stats, strcmp(node->args[0], "echo") == 0, 
		"ft_parse_command with args sets correct args[0]");
	test_assert(stats, strcmp(node->args[1], "hello") == 0, 
		"ft_parse_command with args sets correct args[1]");
	test_assert(stats, strcmp(node->args[2], "world") == 0, 
		"ft_parse_command with args sets correct args[2]");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_command_null_input(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*current;
	t_ast_node	*node;

	shell = test_create_shell();
	current = NULL;
	node = ft_parse_command(shell, &current);
	test_assert(stats, node == NULL, 
		"ft_parse_command returns NULL for NULL input");
	current = test_create_token(shell, TOKEN_PIPE, "|");
	node = ft_parse_command(shell, &current);
	test_assert(stats, node == NULL, 
		"ft_parse_command returns NULL for non-WORD token");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_tokens_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next = test_create_token(shell, TOKEN_WORD, "hello");
	tokens->next->next = test_create_token(shell, TOKEN_END, "");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, "ft_parse_tokens returns non-NULL");
	test_assert(stats, ast->type == AST_COMMAND, 
		"ft_parse_tokens creates AST_COMMAND");
	test_assert(stats, ast->argc == 2, "ft_parse_tokens sets correct argc");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_tokens_with_pipe(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next = test_create_token(shell, TOKEN_WORD, "hello");
	tokens->next->next = test_create_token(shell, TOKEN_PIPE, "|");
	tokens->next->next->next = test_create_token(shell, TOKEN_WORD, "grep");
	tokens->next->next->next->next = test_create_token(shell, TOKEN_WORD, 
		"hello");
	tokens->next->next->next->next->next = test_create_token(shell, TOKEN_END, 
		"");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"ft_parse_tokens with pipe returns non-NULL");
	test_assert(stats, ast->type == AST_PIPE, 
		"ft_parse_tokens with pipe creates AST_PIPE");
	test_assert(stats, ast->left != NULL, 
		"ft_parse_tokens with pipe sets left child");
	test_assert(stats, ast->right != NULL, 
		"ft_parse_tokens with pipe sets right child");
	test_assert(stats, ast->left->type == AST_COMMAND, 
		"ft_parse_tokens pipe left child is AST_COMMAND");
	test_assert(stats, ast->right->type == AST_COMMAND, 
		"ft_parse_tokens pipe right child is AST_COMMAND");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_tokens_null_input(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*ast;

	shell = test_create_shell();
	ast = ft_parse_tokens(shell, NULL);
	test_assert(stats, ast == NULL, 
		"ft_parse_tokens returns NULL for NULL input");
	test_cleanup_shell(shell);
}

void	test_ast_parsing(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Parsing Functions ===\n");
	test_ft_parse_command_simple(&stats);
	test_ft_parse_command_with_args(&stats);
	test_ft_parse_command_null_input(&stats);
	test_ft_parse_tokens_simple(&stats);
	test_ft_parse_tokens_with_pipe(&stats);
	test_ft_parse_tokens_null_input(&stats);
	test_summary(&stats, "AST Parsing");
}