/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:34 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/02 20:29:24 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.tokens = NULL;
	shell.memory_list = NULL;
	shell.exit = 1;
	shell.last_exit_status = 0;
	shell.envp = ft_envp_cpy(&shell, envp);
	shell.is_interactive = isatty(STDIN_FILENO);
	shell.syntax_error = false;
	ft_minishell_loop(&shell);
	return (shell.last_exit_status);
}
