/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:47 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/06 15:46:39 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unity/unity.h"
#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include <string.h>

#ifndef MAX_ARG_COUNT
# define MAX_ARG_COUNT 10
#endif

// Setup and teardown functions (run before/after each test)
void setUp(void)
{}

void tearDown(void)
{}

void test_ft_exec_command_basic(void)
{
	t_command	cmd;
	t_shell		shell;
	char		cwd[PATH_MAX];

	shell.memory_list = NULL;
	cmd.envp = NULL;
	cmd.exit_val = 0;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	getcwd(cwd, PATH_MAX);
	printf("cwd: '%s'\n", cwd);
	
	printf("\n--Run command 'ls'--\n");
	cmd.cmdname = "/usr/bin/ls";
	cmd.args = ft_track_malloc(&shell, sizeof(char *) * MAX_ARG_COUNT);
	cmd.args[0] = cmd.cmdname;
	cmd.args[1] = NULL;

	// TEST_ASSERT_NOT_NULL(dup);				// Check allocation succeeded
	// TEST_ASSERT_EQUAL_STRING("hello", dup);	// Check content matches
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "ls"

	printf("\n--Run command 'ls -la'--\n");
	ft_track_free(&shell, cmd.args);
	// cmd.args = ft_track_malloc(&shell, sizeof(char *) * 3);
	cmd.args[0] = cmd.cmdname;
	cmd.args[1] = "-la";
	cmd.args[2] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "ls -la"

	printf("\n--Run command 'ls -e'--\n");	
	cmd.args[1] = "-e";
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(2, cmd.exit_val);	// Run command "ls -e"

	printf("\n--Run command 'rm' with wrong pathname --\n");
	cmd.cmdname = "rm";
	cmd.args[0] = "/usr/bin/rm";
	cmd.args[1] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(1, cmd.exit_val);	// Run command "ls" with wrong path
	
	printf("\n--Run command 'touch aaa'--\n");	
	cmd.cmdname = "/usr/bin/touch";
	cmd.args[0] = "/usr/bin/touch";
	cmd.args[1] = "aaa";
	cmd.args[2] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "touch aaa"
	
	printf("\n--Run command '/bin/sh ./aaa'--\n");	
	cmd.cmdname = "/bin/sh";
	cmd.args[0] = "/bin/sh";
	cmd.args[1] = "./aaa";
	cmd.args[2] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "/bin/sh aaa"
	
	printf("\n--Run command './aaa'--\n");	
	// cmd.pathname = add_cwd(&shell, cwd, "./aaa");
	cmd.cmdname = "./aaa";
	cmd.args[0] = cmd.cmdname;
	cmd.args[1] = NULL;
	printf("path: '%s\n'", cmd.cmdname);
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(127, cmd.exit_val);	// Run command "touch aaa"
	// ft_track_free(&shell, cmd.pathname);
	
	printf("\n--Run command 'chmod +x aaa'--\n");	
	cmd.cmdname = "/usr/bin/chmod";
	cmd.args[0] = "/usr/bin/chmod";
	cmd.args[1] = "+x";
	cmd.args[2] = "aaa";
	cmd.args[3] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "touch aaa"
	
	printf("\n--Run command './aaa'--\n");	
	// cmd.pathname = add_cwd(&shell, cwd, "./lsaaa");
	cmd.cmdname = "./aaa";
	cmd.args[0] = cmd.cmdname;
	cmd.args[1] = NULL;
	printf("path: '%s\n'", cmd.cmdname);
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "touch aaa"
	// ft_track_free(&shell, cmd.pathname);
	
	printf("\n--Run command 'rm aaa'--\n");	
	cmd.cmdname = "/usr/bin/rm";
	cmd.args[0] = "/usr/bin/rm";
	cmd.args[1] = "aaa";
	cmd.args[2] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(0, cmd.exit_val);	// Run command "rm aaa"

	printf("\n--Run command 'rm aaa'--\n");	
	cmd.cmdname = "/usr/bin/rm";
	cmd.args[0] = "/usr/bin/rm";
	cmd.args[1] = "aaa";
	cmd.args[2] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(1, cmd.exit_val);	// Run command "rm aaa"
	
	printf("\n--Run command 'bbbbbbb'--\n");	
	cmd.cmdname = "bbbbbbb";
	cmd.args[0] = NULL;
	ft_exec_command(&shell, &cmd);
	TEST_ASSERT_EQUAL(127, cmd.exit_val);	// Run command "rm aaa"
	
	printf("\nexit_val: %d\n", cmd.exit_val);	
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
