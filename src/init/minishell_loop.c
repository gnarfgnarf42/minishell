/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 19:35:59 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	ft_check_exit_conditions(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		printf("exit\n");
		free(input);
		return (0);
	}
	return (1);
}

static void	ft_process_input(t_shell *shell, char *tracked_input)
{
	t_token	*tokens;

	tokens = ft_tokenize(shell, tracked_input);
	if (tokens)
	{
		ft_free_tokens(shell, &tokens);
	}
}

static int	ft_handle_input(t_shell *shell, char *input)
{
	char	*tracked_input;

	if (!ft_check_exit_conditions(input))
		return (0);
	add_history(input);
	tracked_input = ft_track_strdup(shell, input);
	free(input);
	if (!tracked_input)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	ft_process_input(shell, tracked_input);
	ft_track_free(shell, tracked_input);
	return (1);
}

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;

	shell->last_exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!ft_handle_input(shell, input))
			break ;
	}
	ft_free_all_tracked(shell);
}
