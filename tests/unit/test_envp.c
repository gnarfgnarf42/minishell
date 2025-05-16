/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:57:16 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 12:49:47 by nefimov          ###   ########.fr       */
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

void setUp(void)
{}

void tearDown(void)
{}

void test_ft_ms_env(void)
{
	t_shell shell;
	char	*envp[MAX_ARG_COUNT];

	// envp[0] = "A=A1";
	envp[0] = "A=A1";
	envp[1] = "B=B2";
	envp[2] = "C=C3";
	envp[3] = NULL;
	shell.tokens = NULL;
	shell.memory_list = NULL;
	shell.envp = envp;

	ft_penv(&shell);
	ft_free_tokens(&shell, &shell.tokens);
}

void test_ft_env_cpy(void)
{
	t_shell shell;
	char	*envp[MAX_ARG_COUNT];
	int		num;
	int		i;

	envp[0] = "A=A1";
	envp[1] = "B=";
	envp[2] = "C=C3";
	envp[3] = NULL;
	num = 4;
	shell.tokens = NULL;
	shell.memory_list = NULL;
	shell.envp = envp;
	ft_penv(&shell);
	printf("\n");
	
	shell.envp = ft_envp_cpy(&shell, envp);
	ft_penv(&shell);
	
	i = -1;
	while (++i < num)
		TEST_ASSERT_EQUAL_STRING(envp[i], shell.envp[i]);
	ft_free_tokens(&shell, &shell.tokens);
}

void test_ft_getenv(void)
{
	t_shell shell;
	char	*envp[MAX_ARG_COUNT];
	char	*name;
	char	*value;
	char	*result;

	envp[0] = "A=A1";
	// envp[0] = NULL;
	envp[1] = "B=";
	envp[2] = "C=C3";
	envp[3] = "D";
	envp[4] = "FF=FF/FFF/FFF";
	envp[5] = NULL;
	shell.tokens = NULL;
	shell.memory_list = NULL;
	shell.envp = envp;
	shell.envp = ft_envp_cpy(&shell, envp);


	ft_penv(&shell);
	printf("\n");
	
	name = "A";
	result = "A1";
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);

	name = "B";
	result = "";
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);

	name = "C";
	result = "C3";
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);

	name = "D";
	result = NULL;
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);

	name = "F";
	result = NULL;
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);
	
	name = "FF";
	result = "FF/FFF/FFF";
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);
	
	name = "FFF";
	result = NULL;
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);

	name = "PATH";
	result = NULL;
	value = ft_getenv(&shell, name);
	printf("%s: '%s'\n", name, value);
	TEST_ASSERT_EQUAL_STRING(result, value);
	
	ft_free_tokens(&shell, &shell.tokens);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_ms_env);
	
	write(1, "\n", 2);
	RUN_TEST(test_ft_env_cpy);

	write(1, "\n", 2);
	RUN_TEST(test_ft_getenv);

	return UNITY_END();
}