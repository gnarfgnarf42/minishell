/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H

# include "../includes/minishell.h"
# include "../includes/parser.h"
# include "../includes/execution.h"
# include <assert.h>
# include <stdio.h>
# include <string.h>

# define TEST_PASS "\033[32m[PASS]\033[0m"
# define TEST_FAIL "\033[31m[FAIL]\033[0m"
# define TEST_INFO "\033[34m[INFO]\033[0m"

typedef struct s_test_stats
{
	int	total;
	int	passed;
	int	failed;
}	t_test_stats;

// Test framework functions
void		test_init(t_test_stats *stats);
void		test_assert(t_test_stats *stats, int condition, 
				const char *test_name);
void		test_summary(t_test_stats *stats, const char *suite_name);
t_shell		*test_create_shell(void);
void		test_cleanup_shell(t_shell *shell);
t_token		*test_create_token(t_shell *shell, t_token_type type, 
				const char *value);
void		test_print_ast(t_ast_node *node, int depth);

// Test suite declarations
void		test_ast_creation(void);
void		test_ast_parsing(void);
void		test_ast_pipeline(void);
void		test_ast_execution(void);
void		test_ast_edge_cases(void);
void		test_ast_integration(void);

#endif