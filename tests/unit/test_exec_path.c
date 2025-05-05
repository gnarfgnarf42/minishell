/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:47 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/05 15:01:27 by nefimov          ###   ########.fr       */
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
	str = get_next_path(NULL, PATH_DELIMITER);
	printf("str: '%s'\n", str);
	TEST_ASSERT_EQUAL_STRING("/usr/local/sbin", str);
	str = get_next_path(NULL, PATH_DELIMITER);
	printf("str: '%s'\n", str);
	TEST_ASSERT_EQUAL_STRING("/usr/local/bin", str);
	str = get_next_path(NULL, PATH_DELIMITER);
	printf("str: '%s'\n", str);
	TEST_ASSERT_NULL(str);
	
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
	
	cmd.pathname = "cmake";
	cur_path = "/usr/local/bin";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("/usr/local/bin/cmake", full_path);
	ft_track_free(&shell, full_path);

	cmd.pathname = "cmake";
	cur_path = "/usr/local/bin/";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("/usr/local/bin/cmake", full_path);
	ft_track_free(&shell, full_path);

	cmd.pathname = "";
	cur_path = "/usr/local/bin";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("/usr/local/bin/", full_path);
	ft_track_free(&shell, full_path);

	cmd.pathname = "cmake";
	cur_path = "";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("cmake", full_path);
	ft_track_free(&shell, full_path);

	cmd.pathname = "";
	cur_path = "";
	full_path = get_full_path(&shell, &cmd, cur_path);
	printf("cur_path: '%s' | full_path: '%s'\n", cur_path, full_path);
	TEST_ASSERT_EQUAL_STRING("", full_path);
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
	
	cmd.pathname = "cmake";
	printf("pathname: '%s' | ", cmd.pathname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.pathname);
	TEST_ASSERT_EQUAL_INT(0, in_path);
	ft_track_free(&shell, cmd.pathname);

	cmd.pathname = "cron";
	printf("pathname: '%s' | ", cmd.pathname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.pathname);
	TEST_ASSERT_EQUAL_INT(0, in_path);
	ft_track_free(&shell, cmd.pathname);

	cmd.pathname = "x86_64-linux-gnu-g++";
	printf("pathname: '%s' | ", cmd.pathname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.pathname);
	TEST_ASSERT_EQUAL_INT(0, in_path);
	ft_track_free(&shell, cmd.pathname);

	cmd.pathname = "";
	printf("pathname: '%s' | ", cmd.pathname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.pathname);
	perror("perror");
	TEST_ASSERT_EQUAL_INT(1, in_path);
	ft_track_free(&shell, cmd.pathname);

	cmd.pathname = "bbbbb";
	printf("pathname: '%s' | ", cmd.pathname);
	in_path = search_in_path(&shell, &cmd);
	printf("in_path: %d | full_path: '%s'\n", in_path, cmd.pathname);
	perror("perror");
	TEST_ASSERT_EQUAL_INT(1, in_path);
	ft_track_free(&shell, cmd.pathname);


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
	
	path = "/usr/bin/";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(0, is_dir);
	
	path = "usr/bin/";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(1, is_dir);
	
	path = "/usr/bin/cccc";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(1, is_dir);
	
	path = "";
	is_dir = path_is_dir(path);
	printf("path: '%s' | out: %d\n", path, is_dir);
	TEST_ASSERT_EQUAL_INT(1, is_dir);

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

	cmd.pathname = "ls";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(0, ret);

	cmd.pathname = "";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(1, ret);

	cmd.pathname = "bbbbbbb";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(1, ret);

	cmd.pathname = "/usr/bin/ls";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(0, ret);

	cmd.pathname = "/usr/bin/";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(1, ret);

	cmd.pathname = "/usr/bin/l";
	printf("cmd: '%s' -> ", cmd.pathname);
	ret = ft_get_path(&shell, &cmd);
	printf("'%s' | ret: %d\n", cmd.pathname, ret);
	TEST_ASSERT_EQUAL_INT(1, ret);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_get_next_path);
	
	write(1, "\n", 2);
	RUN_TEST(test_get_full_path);
	write(1, "\n", 2);
	RUN_TEST(test_search_in_path);
	write(1, "\n", 2);
	RUN_TEST(test_path_is_dir);
	write(1, "\n", 2);
	RUN_TEST(test_str_is_pathname);
	write(1, "\n", 2);
	RUN_TEST(test_ft_get_path);
	
	return UNITY_END();
}
