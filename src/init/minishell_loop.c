/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/04 15:10:43 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t	g_interrupted;

static void	sigint_handler(int signum)
{
	g_interrupted = signum;
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

static void	tokenize_exec_input(t_shell *shell, char *input)
{
	char	*tracked_input;
	t_token	*tokens;

	if (*input)
		add_history(input);
	tracked_input = ft_track_strdup(shell, input);
	if (tracked_input)
	{
		tokens = ft_tokenize(shell, tracked_input);
		if (tokens && tokens->type != TOKEN_END)
		{
			shell->tokens = tokens;
			ft_exec_shell(shell);
			ft_free_tokens(shell, &tokens);
		}
		else
			ft_check_empty_input(shell, tracked_input);
		ft_track_free(shell, tracked_input);
		rl_done = 1;
	}
	else
	{
		ft_perror("minishell", NULL, "Memory allocation failed");
		shell->exit = 0;
	}
}

static char	*read_input(t_shell *shell)
{
	char	*input;

	if (shell->is_interactive)
		input = readline("minishell> ");
	else
	{
		input = get_next_line(STDIN_FILENO);
		if (input)
			input[ft_strlen(input) - 1] = 0;
	}
	if (!input && shell->is_interactive)
		printf("exit\n");
	return (input);
}

void	ft_minishell_loop(t_shell *shell)
{
	char				*input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_sigint_hook;
	while (shell->exit)
	{
		g_interrupted = 0;
		input = read_input(shell);
		if (input)
		{
			if (!g_interrupted)
				tokenize_exec_input(shell, input);
			free(input);
		}
		else
			break ;
	}
	rl_clear_history();
	ft_free_all_tracked(shell);
}
