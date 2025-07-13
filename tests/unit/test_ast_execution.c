/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_framework.h"

static void	test_ft_ast_to_command_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 1;
	node->args = ft_track_malloc(shell, sizeof(char *) * 2);
	node->args[0] = ft_track_strdup(shell, "echo");
	node->args[1] = NULL;
	cmd = ft_ast_to_command(shell, node);
	test_assert(stats, cmd != NULL, "ft_ast_to_command returns non-NULL");
	test_assert(stats, strcmp(cmd->cmdname, "echo") == 0, 
		"ft_ast_to_command sets correct cmdname");
	test_assert(stats, cmd->argsc == 1, 
		"ft_ast_to_command sets correct argsc");
	test_assert(stats, strcmp(cmd->args[0], "echo") == 0, 
		"ft_ast_to_command sets correct args[0]");
	test_assert(stats, cmd->envp == shell->envp, 
		"ft_ast_to_command sets correct envp");
	test_cleanup_shell(shell);
}

static void	test_ft_ast_to_command_with_args(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 3;
	node->args = ft_track_malloc(shell, sizeof(char *) * 4);
	node->args[0] = ft_track_strdup(shell, "echo");
	node->args[1] = ft_track_strdup(shell, "hello");
	node->args[2] = ft_track_strdup(shell, "world");
	node->args[3] = NULL;
	cmd = ft_ast_to_command(shell, node);
	test_assert(stats, cmd != NULL, 
		"ft_ast_to_command with args returns non-NULL");
	test_assert(stats, cmd->argsc == 3, 
		"ft_ast_to_command with args sets correct argsc");
	test_assert(stats, strcmp(cmd->args[1], "hello") == 0, 
		"ft_ast_to_command with args sets correct args[1]");
	test_assert(stats, strcmp(cmd->args[2], "world") == 0, 
		"ft_ast_to_command with args sets correct args[2]");
	test_cleanup_shell(shell);
}

static void	test_ft_ast_to_command_null_input(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;

	shell = test_create_shell();
	cmd = ft_ast_to_command(shell, NULL);
	test_assert(stats, cmd == NULL, 
		"ft_ast_to_command returns NULL for NULL input");
	node = ft_create_ast_node(shell, AST_PIPE);
	cmd = ft_ast_to_command(shell, node);
	test_assert(stats, cmd == NULL, 
		"ft_ast_to_command returns NULL for non-COMMAND node");
	test_cleanup_shell(shell);
}

static void	test_ft_copy_args_simple(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_COMMAND);
	node->argc = 2;
	node->args = ft_track_malloc(shell, sizeof(char *) * 3);
	node->args[0] = ft_track_strdup(shell, "echo");
	node->args[1] = ft_track_strdup(shell, "test");
	node->args[2] = NULL;
	cmd = ft_init_cmd(shell);
	result = ft_copy_args(shell, cmd, node);
	test_assert(stats, result == 0, "ft_copy_args returns 0 on success");
	test_assert(stats, cmd->args != NULL, "ft_copy_args sets args");
	test_assert(stats, strcmp(cmd->args[0], "echo") == 0, 
		"ft_copy_args copies args[0] correctly");
	test_assert(stats, strcmp(cmd->args[1], "test") == 0, 
		"ft_copy_args copies args[1] correctly");
	test_assert(stats, cmd->args[2] == NULL, 
		"ft_copy_args null-terminates args");
	test_cleanup_shell(shell);
}

static void	test_ft_open_redir_in(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;
	int			fd;

	shell = test_create_shell();
	system("echo 'test content' > /tmp/test_input.txt");
	node = ft_create_ast_node(shell, AST_REDIR_IN);
	node->filename = ft_track_strdup(shell, "/tmp/test_input.txt");
	cmd = ft_init_cmd(shell);
	result = ft_open_redir_in(node, cmd);
	test_assert(stats, result == 0, "ft_open_redir_in returns 0 on success");
	test_assert(stats, cmd->fd_in > 0, "ft_open_redir_in sets valid fd_in");
	fd = cmd->fd_in;
	close(fd);
	unlink("/tmp/test_input.txt");
	test_cleanup_shell(shell);
}

static void	test_ft_open_redir_out(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;
	int			fd;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_REDIR_OUT);
	node->filename = ft_track_strdup(shell, "/tmp/test_output.txt");
	cmd = ft_init_cmd(shell);
	result = ft_open_redir_out(node, cmd);
	test_assert(stats, result == 0, "ft_open_redir_out returns 0 on success");
	test_assert(stats, cmd->fd_out > 0, "ft_open_redir_out sets valid fd_out");
	fd = cmd->fd_out;
	close(fd);
	unlink("/tmp/test_output.txt");
	test_cleanup_shell(shell);
}

static void	test_ft_open_redir_append(t_test_stats *stats)
{
	t_shell		*shell;
	t_ast_node	*node;
	t_command	*cmd;
	int			result;
	int			fd;

	shell = test_create_shell();
	node = ft_create_ast_node(shell, AST_REDIR_APPEND);
	node->filename = ft_track_strdup(shell, "/tmp/test_append.txt");
	cmd = ft_init_cmd(shell);
	result = ft_open_redir_append(node, cmd);
	test_assert(stats, result == 0, 
		"ft_open_redir_append returns 0 on success");
	test_assert(stats, cmd->fd_out > 0, 
		"ft_open_redir_append sets valid fd_out");
	fd = cmd->fd_out;
	close(fd);
	unlink("/tmp/test_append.txt");
	test_cleanup_shell(shell);
}

static void	test_ft_exec_ast_node_null(t_test_stats *stats)
{
	t_shell	*shell;
	int		result;

	shell = test_create_shell();
	result = ft_exec_ast_node(shell, NULL);
	test_assert(stats, result == 0, 
		"ft_exec_ast_node returns 0 for NULL input");
	test_cleanup_shell(shell);
}

void	test_ast_execution(void)
{
	t_test_stats	stats;

	test_init(&stats);
	printf("\n=== Testing AST Execution Functions ===\n");
	test_ft_ast_to_command_simple(&stats);
	test_ft_ast_to_command_with_args(&stats);
	test_ft_ast_to_command_null_input(&stats);
	test_ft_copy_args_simple(&stats);
	test_ft_open_redir_in(&stats);
	test_ft_open_redir_out(&stats);
	test_ft_open_redir_append(&stats);
	test_ft_exec_ast_node_null(&stats);
	test_summary(&stats, "AST Execution");
}