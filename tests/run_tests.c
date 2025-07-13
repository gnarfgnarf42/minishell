/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"

int	main(int argc, char **argv)
{
	printf("\n");
	printf("========================================\n");
	printf("       MINISHELL AST TEST SUITE        \n");
	printf("========================================\n");
	
	if (argc > 1)
	{
		if (strcmp(argv[1], "creation") == 0)
			test_ast_creation();
		else if (strcmp(argv[1], "parsing") == 0)
			test_ast_parsing();
		else if (strcmp(argv[1], "pipeline") == 0)
			test_ast_pipeline();
		else if (strcmp(argv[1], "execution") == 0)
			test_ast_execution();
		else if (strcmp(argv[1], "edge") == 0)
			test_ast_edge_cases();
		else if (strcmp(argv[1], "integration") == 0)
			test_ast_integration();
		else
		{
			printf("Unknown test suite: %s\n", argv[1]);
			printf("Available suites: creation, parsing, pipeline, ");
			printf("execution, edge, integration\n");
			return (1);
		}
	}
	else
	{
		printf("\nRunning all test suites...\n");
		test_ast_creation();
		test_ast_parsing();
		test_ast_pipeline();
		test_ast_execution();
		test_ast_edge_cases();
		test_ast_integration();
	}
	
	printf("========================================\n");
	printf("           TESTS COMPLETED             \n");
	printf("========================================\n\n");
	
	return (0);
}