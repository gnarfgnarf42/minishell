/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:34 by sscholz           #+#    #+#             */
/*   Updated: 2025/06/30 17:39:05 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	shell.envp = ft_envp_cpy(&shell, envp);
	ft_minishell_loop(&shell);
	
	// printf ("Exit status: %i\n", shell.last_exit_status);
	return (shell.last_exit_status);
}
