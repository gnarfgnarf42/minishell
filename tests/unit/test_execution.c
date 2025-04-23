/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:47 by nefimov           #+#    #+#             */
/*   Updated: 2025/04/23 17:18:31 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unity/unity.h"
#include "../../includes/minishell.h"
#include "../../includes/execution.h"

// Setup and teardown functions (run before/after each test)
void setUp(void)
{}

void tearDown(void)
{}

void test_ft_exec_command_basic(void)
{
	t_command	cmd;
	t_shell		shell;

	shell.memory_list = NULL;
	cmd.envp = NULL;
	cmd.exit_val = 0;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	
	printf("--Run command 'ls'--\n");
	cmd.pathname = "/usr/bin/ls";
	cmd.args = ft_track_malloc(&shell, sizeof(char *) * 2);
	cmd.args[0] = cmd.pathname;
	cmd.args[1] = NULL;

	// TEST_ASSERT_NOT_NULL(dup);				// Check allocation succeeded
	// TEST_ASSERT_EQUAL_STRING("hello", dup);	// Check content matches
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "ls"

	printf("--Run command 'ls -la'--\n");
	ft_track_free(&shell, cmd.args);
	cmd.args = ft_track_malloc(&shell, sizeof(char *) * 3);
	cmd.args[0] = cmd.pathname;
	cmd.args[1] = "-la";
	cmd.args[2] = NULL;
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "ls -la"

	printf("--Run command 'ls -e'--\n");	
	cmd.args[1] = "-e";
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(2, cmd.exit_val);	// Run command "ls -e"

	printf("--Run command with pathname 'ls'--\n");
	cmd.pathname = "ls";
	cmd.args[0] = "/usr/bin/ls";
	cmd.args[1] = NULL;
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(127, cmd.exit_val);	// Run command "ls" with wrong path
	
	cmd.pathname = "/usr/bin/touch";
	cmd.args[0] = "/usr/bin/touch";
	cmd.args[1] = "aaa";
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "touch aaa"
	
	cmd.pathname = "/usr/bin/rm";
	cmd.args[0] = "/usr/bin/rm";
	cmd.args[1] = "aaa";
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "rm aaa"

	cmd.pathname = "/usr/bin/rm";
	cmd.args[0] = "/usr/bin/rm";
	cmd.args[1] = "aaa";
	ft_exec_command(&cmd);
	TEST_ASSERT_EQUAL(1, cmd.exit_val);	// Run command "rm aaa"
	
	printf("At exit exit_val: %d\n", cmd.exit_val);	
	ft_free_all_tracked(&shell);				// Clean up
	TEST_ASSERT_NULL(shell.memory_list); 		// Check memory list is empty
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_exec_command_basic);
	
	// write(1, "\n", 2);
	// RUN_TEST(test_ft_track_malloc_basic);
	return UNITY_END();
}
