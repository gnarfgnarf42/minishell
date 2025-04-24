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

static void	ft_print_tokens(t_token *cur)
{
	while (cur)
	{
		printf("Token type: %d   ", cur->type);
		if (cur->type == TOKEN_VAR)
			printf("VAR: ");
		else if (cur->type == TOKEN_WORD)
			printf("WORD: ");
		else if (cur->type == TOKEN_PIPE)
			printf("PIPE: ");
		else if (cur->type == TOKEN_REDIR_IN)
			printf("REDIR_IN: ");
		else if (cur->type == TOKEN_REDIR_OUT)
			printf("REDIR_OUT: ");
		else if (cur->type == TOKEN_HEREDOC)
			printf("HEREDOC: ");
		else if (cur->type == TOKEN_APPEND)
			printf("APPEND: ");
		else if (cur->type == TOKEN_AND)
			printf("AND: ");
		else if (cur->type == TOKEN_OR)
			printf("OR: ");
		else if (cur->type == TOKEN_LPAREN)
			printf("LPAREN: ");
		else if (cur->type == TOKEN_RPAREN)
			printf("RPAREN: ");
		else if (cur->type == TOKEN_END)
			printf("END: ");
		else
			printf("UNKNOWN: ");
		printf("\"%s\"\n", cur->value);
		cur = cur->next;
	}
}

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;
	char	*tracked_input;
	t_token	*tokens;

	shell->last_exit_status = 0;
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
