/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_edge_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_parse_empty_tokens(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_END, "");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast == NULL, 
		"ft_parse_tokens returns NULL for empty token list");
	test_cleanup_shell(shell);
}

static void	test_parse_only_operators(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*node;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_PIPE, "|");
	current = tokens;
	node = ft_parse_command(shell, &current);
	test_assert(stats, node == NULL, 
		"ft_parse_command returns NULL for pipe token");
	tokens = test_create_token(shell, TOKEN_REDIR_OUT, ">");
	current = tokens;
	node = ft_parse_command(shell, &current);
	test_assert(stats, node == NULL, 
		"ft_parse_command returns NULL for redirection token");
	test_cleanup_shell(shell);
}

static void	test_parse_incomplete_redirection(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_OUT, ">");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result == NULL, 
		"ft_parse_redirections returns NULL for incomplete redirection");
	test_cleanup_shell(shell);
}

static void	test_parse_redirection_wrong_token(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_token		*current;
	t_ast_node	*cmd;
	t_ast_node	*result;

	shell = test_create_shell();
	cmd = ft_create_ast_node(shell, AST_COMMAND);
	tokens = test_create_token(shell, TOKEN_REDIR_OUT, ">");
	tokens->next = test_create_token(shell, TOKEN_PIPE, "|");
	current = tokens;
	result = ft_parse_redirections(shell, &current, cmd);
	test_assert(stats, result == NULL, 
		"ft_parse_redirections returns NULL for wrong token type");
	test_cleanup_shell(shell);
}

static void	test_open_nonexistent_file(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_REDIR_IN);
	node->filename = ft_track_strdup(shell, "/nonexistent/file.txt");
	cmd = ft_init_cmd(shell);
	result = ft_open_redir_in(node, cmd);
	test_assert(stats, result == 1, 
		"ft_open_redir_in returns 1 for nonexistent file");
	test_assert(stats, cmd->fd_in == -1, 
		"ft_open_redir_in sets fd_in to -1 on error");
	test_cleanup_shell(shell);
}

static void	test_open_invalid_path(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_REDIR_OUT);
	node->filename = ft_track_strdup(shell, "/root/forbidden.txt");
	cmd = ft_init_cmd(shell);
	result = ft_open_redir_out(node, cmd);
	test_assert(stats, result == 1, 
		"ft_open_redir_out returns 1 for forbidden path");
	test_cleanup_shell(shell);
}

static void	test_ast_to_command_empty_args(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 0;
	node->args = NULL;
	cmd = ft_ast_to_command(shell, node);
	test_assert(stats, cmd != NULL, 
		"ft_ast_to_command handles empty args");
	test_assert(stats, cmd->argsc == 0, 
		"ft_ast_to_command sets argsc to 0 for empty args");
	test_assert(stats, cmd->args != NULL, 
		"ft_ast_to_command initializes args array for empty args");
	test_cleanup_shell(shell);
}

static void	test_copy_args_zero_argc(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 0;
	node->args = NULL;
	cmd = ft_init_cmd(shell);
	result = ft_copy_args(shell, cmd, node);
	test_assert(stats, result == 0, 
		"ft_copy_args returns 0 for zero argc");
	test_cleanup_shell(shell);
}

static void	test_parse_parentheses_skipping(t_test_stats *stats)
{
	t_shell		*shell;
	t_token		*tokens;
	t_ast_node	*ast;

	shell = test_create_shell();
	tokens = test_create_token(shell, TOKEN_LPAREN, "(");
	tokens->next = test_create_token(shell, TOKEN_RPAREN, ")");
	tokens->next->next = test_create_token(shell, TOKEN_WORD, "echo");
	tokens->next->next->next = test_create_token(shell, TOKEN_WORD, "hello");
	tokens->next->next->next->next = test_create_token(shell, TOKEN_END, "");
	ast = ft_parse_tokens(shell, tokens);
	test_assert(stats, ast != NULL, 
		"ft_parse_tokens skips parentheses and parses command");
	test_assert(stats, ast->type == AST_COMMAND, 
		"ft_parse_tokens creates command after skipping parentheses");
	test_cleanup_shell(shell);
}

void	test_ast_edge_cases(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Edge Cases ===\n");
	test_parse_empty_tokens(&stats);
	test_parse_only_operators(&stats);
	test_parse_incomplete_redirection(&stats);
	test_parse_redirection_wrong_token(&stats);
	test_open_nonexistent_file(&stats);
	test_open_invalid_path(&stats);
	test_ast_to_command_empty_args(&stats);
	test_copy_args_zero_argc(&stats);
	test_parse_parentheses_skipping(&stats);
	test_summary(&stats, "AST Edge Cases");
}