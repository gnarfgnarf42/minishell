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

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;
	char	*tracked_input;
	size_t	len;

	while (1)
	{
		printf("minishell$ ");
		fflush(stdout);
		input = NULL;
		len = 0;
		if (getline(&input, &len, stdin) == -1)
		{
			ft_track_free(shell, input);
			printf("\n");
			break ;
		}
		if (input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
		if (ft_strlen(input) == 0)
		{
			ft_track_free(shell, input);
			continue ;
		}
		tracked_input = ft_track_strdup(shell, input);
		if (!tracked_input)
		{
			ft_track_free(shell, input);
			continue ;
		}
		ft_track_free(shell, input);
		printf("You typed: %s\n", input);
		ft_track_free(shell, input);
	}
}

int	main(void)
{
	t_shell	shell;

	shell.memory_list = NULL;

	ft_minishell_loop(&shell);
	ft_free_all_tracked(&shell);
	return (0);
}
