/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:35:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/05/18 16:20:05 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

volatile sig_atomic_t interrupted = 0;

void sigint_handler(int signum)
{
    (void)signum;
    interrupted = 1;
    // write(STDOUT_FILENO, "\n", 1);  // Print newline to reset prompt line
}

int check_sigint_hook(void)
{
    if (interrupted) {
        rl_done = 1;  // Force readline() to return
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
	struct sigaction	sa;
	
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // You can also try 0 if readline doesn't exit with SA_RESTART
    sigaction(SIGINT, &sa, NULL);

	// Set readline event hook
	rl_event_hook = check_sigint_hook;
	
	shell->last_exit_status = 0;
	
	while (1)
	{
		interrupted = 0;
		
		// rl_on_new_line();              // Tell readline a new line is starting
		// rl_replace_line("", 0); 
		input = readline("minishell> ");
		// printf("readline: '%s'\n", input);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (interrupted) {
            // If readline was interrupted, restart loop
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
	}
	ft_free_all_tracked(shell);
}
