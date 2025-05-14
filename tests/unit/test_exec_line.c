/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:47 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/13 17:37:07 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unity/unity.h"
#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/parser.h"
#include <string.h>
#include <stdio.h>

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#ifndef MAX_ARG_COUNT
# define MAX_ARG_COUNT 10
#endif

void check_open_fds()
{
    DIR *dir = opendir("/proc/self/fd");
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("Open FD: %s\n", entry->d_name);
        }
        closedir(dir);
    }
	else
		printf("All FD are closed\n");
}

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

	// check_open_fds();
	shell.tokens = NULL;
	shell.memory_list = NULL;
	
	// input_line = "ls -la <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat";
	input_line = "cat <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat";
	// input_line = "cat <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat < tests/files/simple_text_2";
	
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
	
	ft_free_cmd_line(&shell, cmd_line);
	ft_free_tokens(&shell, &shell.tokens);
	// check_open_fds();
}

void test_create_cmd_line(void)
{
	char		*input_line;
	t_command	*cmd;
	t_command	*cmd_line;
	t_shell		shell;
	// t_token		*tkn;

	// check_open_fds();
	shell.tokens = NULL;
	shell.memory_list = NULL;
	
	// input_line = "ls -la <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat";
	input_line = "cat <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat | ls | echo aaa";
	// input_line = "cat <tests/files/simple_text >tests/files/out >>tests/files/app <<hd | cat < tests/files/simple_text_2";
	
	printf("Input line: '%s'\n", input_line);
	shell.tokens = ft_tokenize(&shell, input_line);
	// ft_print_tokens(shell.tokens);
	printf("\n");
	
	cmd_line = ft_create_cmd_line(&shell);
		
	cmd = cmd_line;
	while (cmd)
	{
		if (cmd->exit_val == 0)
		{
			ft_print_cmd(cmd);	
			// ft_exec_command(&shell, cmd);
		}
		cmd = cmd->next;
	}
	ft_free_cmd_line(&shell, cmd_line);
	ft_free_tokens(&shell, &shell.tokens);
	printf("\n");
	check_open_fds();
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_process_token);
	
	write(1, "\n", 2);
	RUN_TEST(test_create_cmd_line);

	return UNITY_END();
}
