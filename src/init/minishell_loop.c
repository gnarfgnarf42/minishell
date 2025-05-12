/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/05/11 11:02:15 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token type: %d\n", current->type); // Debug
		if (current->type == TOKEN_WORD)
			printf("WORD: ");
		else if (current->type == TOKEN_PIPE)
			printf("PIPE: ");
		else if (current->type == TOKEN_REDIR_IN)
			printf("REDIR_IN: ");
		else if (current->type == TOKEN_REDIR_OUT)
			printf("REDIR_OUT: ");
		else if (current->type == TOKEN_END)
			printf("END: ");
		else
			printf("UNKNOWN: ");
		if (current->value)
			printf("\"%s\"\n", current->value);
		else
			printf("\"\"\"\n");
		current = current->next;
	}
}

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;
	char	*tracked_input;
	t_token	*tokens;

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
			printf("exit\n");
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
		tokens = ft_tokenize(shell, tracked_input);
		if (tokens)
		{
			ft_print_tokens(tokens);
			ft_free_tokens(shell, &tokens);
		}
		ft_track_free(shell, tracked_input);
	}
	ft_free_all_tracked(shell);
}
