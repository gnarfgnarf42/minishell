/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:34 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/17 19:22:37 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;
	char	*tracked_input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		add_history(input);
		tracked_input = ft_track_strdup(shell, input);
		free(input);
		if (!tracked_input)
		{
			printf("Error: Memory allocation failed\n");
			break ;
		}
		printf("You entered: %s\n", tracked_input);
		ft_track_free(shell, tracked_input);
	}
	ft_free_all_tracked(shell);
}

int	main(void)
{
	t_shell	shell;

	shell.memory_list = NULL;

	ft_minishell_loop(&shell);
	return (0);
}
