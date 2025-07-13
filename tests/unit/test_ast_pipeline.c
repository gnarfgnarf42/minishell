/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_ft_parse_redirections_input(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_IN, "<");
	tokens->next = test_create_token(shell, TOKEN_WORD, "input.txt");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result != NULL, 
		"ft_parse_redirections input returns non-NULL");
	test_assert(stats, result->type == AST_REDIR_IN, 
		"ft_parse_redirections input creates AST_REDIR_IN");
	test_assert(stats, strcmp(result->filename, "input.txt") == 0, 
		"ft_parse_redirections input sets correct filename");
	test_assert(stats, result->left == cmd, 
		"ft_parse_redirections input sets correct left child");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_redirections_output(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_OUT, ">");
	tokens->next = test_create_token(shell, TOKEN_WORD, "output.txt");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result != NULL, 
		"ft_parse_redirections output returns non-NULL");
	test_assert(stats, result->type == AST_REDIR_OUT, 
		"ft_parse_redirections output creates AST_REDIR_OUT");
	test_assert(stats, strcmp(result->filename, "output.txt") == 0, 
		"ft_parse_redirections output sets correct filename");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_redirections_append(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_APPEND, ">>");
	tokens->next = test_create_token(shell, TOKEN_WORD, "append.txt");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result != NULL, 
		"ft_parse_redirections append returns non-NULL");
	test_assert(stats, result->type == AST_REDIR_APPEND, 
		"ft_parse_redirections append creates AST_REDIR_APPEND");
	test_assert(stats, strcmp(result->filename, "append.txt") == 0, 
		"ft_parse_redirections append sets correct filename");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_redirections_heredoc(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_HEREDOC, "<<");
	tokens->next = test_create_token(shell, TOKEN_WORD, "EOF");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result != NULL, 
		"ft_parse_redirections heredoc returns non-NULL");
	test_assert(stats, result->type == AST_REDIR_HEREDOC, 
		"ft_parse_redirections heredoc creates AST_REDIR_HEREDOC");
	test_assert(stats, strcmp(result->filename, "EOF") == 0, 
		"ft_parse_redirections heredoc sets correct filename");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_redirections_multiple(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_IN, "<");
	tokens->next = test_create_token(shell, TOKEN_WORD, "input.txt");
	tokens->next->next = test_create_token(shell, TOKEN_REDIR_OUT, ">");
	tokens->next->next->next = test_create_token(shell, TOKEN_WORD, 
		"output.txt");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result != NULL, 
		"ft_parse_redirections multiple returns non-NULL");
	test_assert(stats, result->type == AST_REDIR_OUT, 
		"ft_parse_redirections multiple outer type is AST_REDIR_OUT");
	test_assert(stats, result->left->type == AST_REDIR_IN, 
		"ft_parse_redirections multiple inner type is AST_REDIR_IN");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_pipeline_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*result;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next = test_create_token(shell, TOKEN_WORD, "hello");
	current = tokens;
	result = ft_parse_pipeline(shell, &current);
	test_assert(stats, result != NULL, 
		"ft_parse_pipeline simple returns non-NULL");
	test_assert(stats, result->type == AST_COMMAND, 
		"ft_parse_pipeline simple creates AST_COMMAND");
	test_assert(stats, result->argc == 2, 
		"ft_parse_pipeline simple sets correct argc");
	test_cleanup_shell(shell);
}

static void	test_ft_parse_pipeline_with_pipe(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*result;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next = test_create_token(shell, TOKEN_WORD, "hello");
	tokens->next->next = test_create_token(shell, TOKEN_PIPE, "|");
	tokens->next->next->next = test_create_token(shell, TOKEN_WORD, "grep");
	tokens->next->next->next->next = test_create_token(shell, TOKEN_WORD, 
		"hello");
	current = tokens;
	result = ft_parse_pipeline(shell, &current);
	test_assert(stats, result != NULL, 
		"ft_parse_pipeline with pipe returns non-NULL");
	test_assert(stats, result->type == AST_PIPE, 
		"ft_parse_pipeline with pipe creates AST_PIPE");
	test_assert(stats, result->left->type == AST_COMMAND, 
		"ft_parse_pipeline pipe left is AST_COMMAND");
	test_assert(stats, result->right->type == AST_COMMAND, 
		"ft_parse_pipeline pipe right is AST_COMMAND");
	test_cleanup_shell(shell);
}

void	test_ast_pipeline(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Pipeline Functions ===\n");
	test_ft_parse_redirections_input(&stats);
	test_ft_parse_redirections_output(&stats);
	test_ft_parse_redirections_append(&stats);
	test_ft_parse_redirections_heredoc(&stats);
	test_ft_parse_redirections_multiple(&stats);
	test_ft_parse_pipeline_simple(&stats);
	test_ft_parse_pipeline_with_pipe(&stats);
	test_summary(&stats, "AST Pipeline");
}