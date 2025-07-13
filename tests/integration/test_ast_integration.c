/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_integration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_full_pipeline_echo_grep(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "echo hello world | grep hello");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Full pipeline tokenize->parse succeeds");
	test_assert(stats, ast->type == AST_PIPE, 
		"Full pipeline creates pipe AST");
	test_assert(stats, ast->left->type == AST_COMMAND, 
		"Full pipeline left side is command");
	test_assert(stats, ast->right->type == AST_COMMAND, 
		"Full pipeline right side is command");
	test_assert(stats, ast->left->argc == 3, 
		"Full pipeline left command has 3 args");
	test_assert(stats, ast->right->argc == 2, 
		"Full pipeline right command has 2 args");
	test_cleanup_shell(shell);
}

static void	test_full_redirection_echo_output(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "echo hello > output.txt");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Full redirection tokenize->parse succeeds");
	test_assert(stats, ast->type == AST_REDIR_OUT, 
		"Full redirection creates output redirection AST");
	test_assert(stats, ast->left->type == AST_COMMAND, 
		"Full redirection command is correct");
	test_assert(stats, strcmp(ast->filename, "output.txt") == 0, 
		"Full redirection filename is correct");
	test_cleanup_shell(shell);
}

static void	test_full_complex_pipeline(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "cat file.txt | grep pattern | wc -l");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Complex pipeline tokenize->parse succeeds");
	test_assert(stats, ast->type == AST_PIPE, 
		"Complex pipeline creates pipe AST");
	test_assert(stats, ast->left->type == AST_PIPE, 
		"Complex pipeline left side is also pipe");
	test_assert(stats, ast->right->type == AST_COMMAND, 
		"Complex pipeline right side is command");
	test_cleanup_shell(shell);
}

static void	test_full_redirection_with_pipe(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "echo hello | grep hello > result.txt");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Pipe with redirection tokenize->parse succeeds");
	test_assert(stats, ast->type == AST_PIPE, 
		"Pipe with redirection creates pipe AST");
	test_assert(stats, ast->right->type == AST_REDIR_OUT, 
		"Pipe with redirection right side has redirection");
	test_assert(stats, ast->right->left->type == AST_COMMAND, 
		"Pipe with redirection command is nested correctly");
	test_cleanup_shell(shell);
}

static void	test_full_multiple_redirections(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "cat < input.txt > output.txt");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Multiple redirections tokenize->parse succeeds");
	test_assert(stats, ast->type == AST_REDIR_OUT, 
		"Multiple redirections outer type is output");
	test_assert(stats, ast->left->type == AST_REDIR_IN, 
		"Multiple redirections inner type is input");
	test_assert(stats, ast->left->left->type == AST_COMMAND, 
		"Multiple redirections command is nested correctly");
	test_cleanup_shell(shell);
}

static void	test_memory_management_integration(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;
	int			initial_count;
	int			final_count;

	shell = test_create_shell();
	initial_count = 0;
	if (shell->memory_list)
	{
		t_track *track = shell->memory_list;
		while (track)
		{
			initial_count++;
			track = track->next;
		}
	}
	tokens = ft_tokenize(shell, "echo hello | grep hello");
	ast = ft_parse_tokens(shell, tokens);
	ft_free_ast(shell, ast);
	ft_free_tokens(shell, &tokens);
	final_count = 0;
	if (shell->memory_list)
	{
		t_track *track = shell->memory_list;
		while (track)
		{
			final_count++;
			track = track->next;
		}
	}
	test_assert(stats, final_count == initial_count, 
		"Memory management: all AST memory properly freed");
	test_cleanup_shell(shell);
}

static void	test_tokenize_parse_execute_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;
	int			result;

	shell = test_create_shell();
	tokens = ft_tokenize(shell, "echo test");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"Tokenize->Parse->Execute: parsing succeeds");
	shell->ast = ast;
	result = ft_exec_ast_node(shell, ast);
	test_assert(stats, result >= 0, 
		"Tokenize->Parse->Execute: execution returns valid code");
	ft_free_ast(shell, ast);
	ft_free_tokens(shell, &tokens);
	test_cleanup_shell(shell);
}

void	test_ast_integration(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Integration ===\n");
	test_full_pipeline_echo_grep(&stats);
	test_full_redirection_echo_output(&stats);
	test_full_complex_pipeline(&stats);
	test_full_redirection_with_pipe(&stats);
	test_full_multiple_redirections(&stats);
	test_memory_management_integration(&stats);
	test_tokenize_parse_execute_simple(&stats);
	test_summary(&stats, "AST Integration");
}