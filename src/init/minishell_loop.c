/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/02 20:31:44 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t	g_interrupted;

void	sigint_handler(int signum)
{
	(void)signum;
	g_interrupted = 1;
}

static int	check_sigint_hook(void)
{
	if (g_interrupted)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_reset_line_state();
		rl_replace_line("", 0);
		rl_redisplay();
		g_interrupted = 0;
	}
	return (0);
}

static void	print_tokens_bonus(t_token *cur)
{
	if (cur->type == TOKEN_AND)
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
}

void	ft_print_tokens(t_token *cur)
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
		else
			print_tokens_bonus(cur);
		printf("\"%s\"\n", cur->value);
		cur = cur->next;
	}
}

void	ft_minishell_loop(t_shell *shell)
{
	char				*input;
	char				*tracked_input;
	t_token				*tokens;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_sigint_hook;
	while (shell->exit)
	{
		g_interrupted = 0;
		if (shell->is_interactive)
			input = readline("minishell> ");
		else
		{
			input = get_next_line(STDIN_FILENO);
			if (input)
				input[ft_strlen(input) - 1] = 0;
		}
		if (!input)
		{
			if (shell->is_interactive)
				printf("exit\n");
			break ;
		}
		if (g_interrupted)
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		tracked_input = ft_track_strdup(shell, input);
		free(input);
		if (tracked_input)
		{
			tokens = ft_tokenize(shell, tracked_input);
			if (tokens && tokens->type != TOKEN_END)
			{
				// ft_print_tokens(tokens);
				shell->tokens = tokens;
				ft_exec_shell(shell);
				ft_free_tokens(shell, &tokens);
			}
			ft_track_free(shell, tracked_input);
			rl_done = 1;
		}
		else
			shell->exit = ft_perror("minishell", NULL,
					"Memory allocation failed", 0);
	}
	clear_history();
	ft_free_all_tracked(shell);
}
