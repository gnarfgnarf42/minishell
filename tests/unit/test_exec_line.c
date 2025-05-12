/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:47 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/12 12:04:37 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unity/unity.h"
#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/parser.h"
#include <string.h>
#include <stdio.h>

#ifndef MAX_ARG_COUNT
# define MAX_ARG_COUNT 10
#endif

void	ft_print_tokens(t_token *tokens);

// Setup and teardown functions (run before/after each test)
void setUp(void)
{}

void tearDown(void)
{}

void test_ft_process_token(void)
{
	char		*input_line;
	t_command	*cmd;
	t_command	*cmd_line;
	t_shell		shell;
	t_token		*tkn;

	shell.tokens = NULL;
	shell.memory_list = NULL;
	
	input_line = "ls -la < in > out >> app <<hd | pwd";
	printf("Input line: '%s'\n", input_line);
	shell.tokens = ft_tokenize(&shell, input_line);
	ft_print_tokens(shell.tokens);
	printf("\n");
	
	cmd = ft_init_cmd(&shell);
	cmd_line = cmd;
	tkn = shell.tokens;
	if (tkn)
		printf("First token: %d | '%s' | %p\n", tkn->type, tkn->value, tkn);
	while (tkn && tkn->type != 11)
	{
		tkn = ft_process_token(&shell, tkn, &cmd);
		if (tkn)
			printf("Next token: %d | '%s' | %p\n", tkn->type, tkn->value, tkn);
	}
	
	while (cmd_line)
	{
		ft_print_cmd(cmd_line);	
		ft_exec_command(&shell, cmd_line);
		cmd_line = cmd_line->next;
	}
	ft_free_cmd(&shell, cmd);
	ft_free_tokens(&shell, &shell.tokens);
}
/* 
void test_get_next_path(void)
{
	t_command	cmd;
	t_shell		shell;
	char		*path;
	char		*str;

	shell.memory_list = NULL;
	cmd.envp = NULL;
	cmd.exit_val = 0;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	
	path = ft_track_strdup(&shell, "/home/nefimov/bin:/usr/local/sbin:/usr/local/bin");
	printf("path: '%s'\n", path);
	
	str = get_next_path(path, PATH_DELIMITER);
	printf("str: '%s'\n", str);
	TEST_ASSERT_EQUAL_STRING("/home/nefimov/bin", str);
	
	ft_track_free(&shell, path);
	ft_free_all_tracked(&shell);				// Clean up
	TEST_ASSERT_NULL(shell.memory_list); 		// Check memory list is empty
}
void test_get_full_path(void)
{
	t_command	cmd;
	t_shell		shell;
	char		*cur_path;
	char		*full_path;
	
	shell.memory_list = NULL;
	cmd.envp = NULL;
	cmd.exit_val = 0;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	
	cmd.cmdname = "cmake";
	cur_path = "/usr/local/bin";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("/usr/local/bin/cmake", full_path);
	ft_track_free(&shell, full_path);


	ft_free_all_tracked(&shell);				// Clean up
	TEST_ASSERT_NULL(shell.memory_list); 		// Check memory list is empty
}
	
void test_search_in_path(void)
{
	t_command	cmd;
	t_shell		shell;
	int			in_path;
	
	shell.memory_list = NULL;
	cmd.envp = NULL;
	cmd.exit_val = 0;
	cmd.fd_in = STDIN_FILENO;
	cmd.fd_out = STDOUT_FILENO;
	
	cmd.cmdname = "cmake";
	printf("pathname: '%s' | ", cmd.cmdname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.cmdname);
	TEST_ASSERT_EQUAL_INT(0, in_path);
	ft_track_free(&shell, cmd.cmdname);

	ft_free_all_tracked(&shell);				// Clean up
	TEST_ASSERT_NULL(shell.memory_list); 		// Check memory list is empty
}
	
void test_path_is_dir(void)
{
	char	*path;
	int 	is_dir;

	path = "/usr/bin";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(0, is_dir);
	
	path = "/usr/sbin/cron";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(1, is_dir);
}
	
void test_str_is_pathname(void)
{
	TEST_ASSERT_EQUAL_INT(1, str_is_pathname("/"));
	TEST_ASSERT_EQUAL_INT(1, str_is_pathname("/usr/"));
	TEST_ASSERT_EQUAL_INT(1, str_is_pathname("usr/"));
	TEST_ASSERT_EQUAL_INT(1, str_is_pathname("usr/bin"));
	TEST_ASSERT_EQUAL_INT(0, str_is_pathname(""));
	TEST_ASSERT_EQUAL_INT(0, str_is_pathname("usr"));
}

void test_ft_get_path(void)
{
	t_command	cmd;
	t_shell		shell;
	int			ret;

	
	cmd.cmdname = "/usr/bin/l";
	printf("cmd: '%s' -> ", cmd.cmdname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.cmdname, ret);
	TEST_ASSERT_EQUAL_INT(1, ret);
} */

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_process_token);
	
	/* write(1, "\n", 2);
	RUN_TEST(test_get_full_path);
	*/

	return UNITY_END();
}
