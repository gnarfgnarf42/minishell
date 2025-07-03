/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:51:07 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/03 19:34:24 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define TOKEN_SKIP ((t_token *)-1)

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_VAR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_END
} t_token_type;

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
int		ft_is_multichar_start(char c, char next);
t_token	*ft_handle_multichar_op(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_operator(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_paren(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_quotes(t_shell *shell, const char *input, size_t *i);
t_token	*ft_handle_dollar(t_shell *shell, const char *input, size_t *i);

t_token	*ft_handle_word(t_shell *shell, const char *input, size_t *i);
void	ft_add_token(t_token **head, t_token **tail, t_token *new_token);
t_token	*ft_process_char(t_shell *shell, const char *input, size_t *i);
t_token	*ft_finalize_tokens(t_shell *shell, t_token *head);
t_token	*ft_tokenize_loop(t_shell *shell, const char *input, size_t *i);
void	ft_free_tokens(t_shell *shell, t_token **head);

// Variable expansion functions
char	*ft_get_var_value(t_shell *shell, const char *var_name);
char	*ft_expand_variable(t_shell *shell, const char *input, size_t *i);
char	*ft_append_to_result(t_shell *shell, char *result, const char *append);
char	*ft_process_quoted_content(t_shell *shell, const char *input,
			size_t *i, char quote_char);
char	*ft_process_regular_text(t_shell *shell, const char *input, size_t *i);

#endif