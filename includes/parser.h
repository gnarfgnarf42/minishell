/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:51:07 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/26 18:51:09 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_QUOTE,
	TOKEN_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// Tokenizer functions (in src/parser/tokenizer/)
t_token	*ft_tokenize(t_shell *shell, const char *input);
t_token	*ft_create_token(t_shell *shell, t_token_type type,
			const char *value, size_t len);
void	ft_skip_whitespace(const char *input, size_t *i);
t_token	*ft_handle_operator(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_quotes(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_word(t_shell *shell, const char *input, size_t *i);
void	ft_add_token(t_token **head, t_token **tail, t_token *new_token);
t_token	*ft_process_char(t_shell *shell, const char *input, size_t *i);
t_token	*ft_finalize_tokens(t_shell *shell, t_token *head);
t_token	*ft_tokenize_loop(t_shell *shell, const char *input, size_t *i); // New
void	ft_free_tokens(t_shell *shell, t_token **head);

#endif