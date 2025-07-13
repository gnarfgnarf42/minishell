/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"

void	test_init(t_test_stats *stats)
{
	stats->total = 0;
	stats->passed = 0;
	stats->failed = 0;
}

void	test_assert(t_test_stats *stats, int condition, const char *test_name)
{
	stats->total++;
	if (condition)
	{
		stats->passed++;
		printf("%s %s\n", TEST_PASS, test_name);
	}
	else
	{
		stats->failed++;
		printf("%s %s\n", TEST_FAIL, test_name);
	}
}

void	test_summary(t_test_stats *stats, const char *suite_name)
{
	printf("\n%s Test Suite: %s\n", TEST_INFO, suite_name);
	printf("Total: %d, Passed: %d, Failed: %d\n", 
		stats->total, stats->passed, stats->failed);
	if (stats->failed == 0)
		printf("%s All tests passed!\n\n", TEST_PASS);
	else
		printf("%s %d test(s) failed!\n\n", TEST_FAIL, stats->failed);
}

t_shell	*test_create_shell(void)
{
	t_shell	*shell;
	char	*envp[] = {"PATH=/bin:/usr/bin", "HOME=/tmp", NULL};

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->memory_list = NULL;
	shell->cmd_list = NULL;
	shell->envp = envp;
	shell->last_exit_status = 0;
	shell->is_interactive = 0;
	shell->exit = 1;
	shell->syntax_error = 0;
	return (shell);
}

void	test_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_free_all_tracked(shell);
	free(shell);
}

t_token	*test_create_token(t_shell *shell, t_token_type type, 
			const char *value)
{
	t_token	*token;

	token = ft_track_malloc(shell, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_track_strdup(shell, value);
	token->next = NULL;
	return (token);
}

void	test_print_ast(t_ast_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("Type: %d", node->type);
	if (node->args && node->argc > 0)
	{
		printf(", Args: ");
		i = 0;
		while (i < node->argc)
		{
			printf("%s ", node->args[i]);
			i++;
		}
	}
	if (node->filename)
		printf(", File: %s", node->filename);
	printf("\n");
	test_print_ast(node->left, depth + 1);
	test_print_ast(node->right, depth + 1);
}