/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/06/30 12:37:19 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"
#include "parser.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t interrupted;

void sigint_handler(int signum)
{
    (void)signum;
    interrupted = 1;
}

int check_sigint_hook(void)
{
    if (interrupted)
    {
		// rl_replace_line("", 0);    // Clear current input
        // rl_done = 1;
		// write(STDOUT_FILENO, "\n", 1);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_reset_line_state();
    	rl_replace_line("", 0);
    	rl_redisplay();
		interrupted = 0;
    }
    return 0;
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
	char				*input;
	char				*tracked_input;
	t_token				*tokens;
	int					is_interactive;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_sigint_hook;
	shell->last_exit_status = 0;
	is_interactive = isatty(STDIN_FILENO);
	
	while (1)
	{
		interrupted = 0;
		// printf("New input | Inrettuptes: %i\n", interrupted);
		// input = readline("minishell> ");

		if (is_interactive)
            input = readline("minishell> ");
        else
		{
            input = get_next_line(STDIN_FILENO);
			if (input)
            	input[ft_strlen(input) - 1] = 0;
        }
		
		// printf("Input: %s\n", input);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (interrupted)
		{
            free(input);
            continue ;
        }
		if (*input)
            add_history(input);
		tracked_input = ft_track_strdup(shell, input);
		free(input);
		if (!tracked_input)
		{
			printf("Error: Memory allocation failed\n");
			break ;
		}
		// printf("You entered: %s\n", tracked_input);
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
	ft_free_all_tracked(shell);
}
