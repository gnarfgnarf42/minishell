/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:48:58 by sscholz           #+#    #+#             */
/*   Updated: 2025/05/16 14:48:27 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
/*
static void	ft_quote_error(char quote)
{
	static char	double_err[] = "minishell: syntax error: unclosed quote\n";
	static char	single_err[] = "minishell: syntax error: "
		"unclosed single quote\n";

	if (quote == '"')
		write(STDERR_FILENO, double_err, 40);
	else
		write(STDERR_FILENO, single_err, 48);
}

static char	*ft_extract_quoted_string(t_shell *shell, const char *input,
		size_t *i, size_t *len)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	*len = 0;
	while (input[*i + *len] && input[*i + *len] != quote)
		(*len)++;
	if (!input[*i + *len])
		return (NULL);
	return (ft_track_strndup(shell, &input[*i], *len));
}

t_token	*ft_handle_quotes(t_shell *shell, const char *input, size_t *i)
{
	t_token	*token;
	char	*value;
	size_t	len;
	char	quote;

	quote = input[*i];
	value = ft_extract_quoted_string(shell, input, i, &len);
	if (!value)
	{
		ft_quote_error(quote);
		return (NULL);
	}
	token = ft_create_token(shell, TOKEN_WORD, value, len);
	token->glue = true;
	ft_track_free(shell, value);
	if (!token)
		return (NULL);
	*i += len + 1;
	return (token);
}
*/

static void	ft_quote_error(char quote)
{
	static char	double_err[] = "minishell: syntax error: unclosed quote\n";
	static char	single_err[] = "minishell: syntax error: "
		"unclosed single quote\n";

	if (quote == '"')
		write(STDERR_FILENO, double_err, 40);
	else
		write(STDERR_FILENO, single_err, 48);
}

static size_t	get_var_name_len(const char *s)
{
	size_t	len;

	len = 0;
	if (s[0] == '?')
		return (1);
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	return (len);
}

static char	*get_var_value(t_shell *shell, const char *input, size_t *i)
{
	char	*name;
	char	*val;
	char	*env;
	size_t	nlen;

	(*i)++;
	nlen = get_var_name_len(&input[*i]);
	name = ft_track_strndup(shell, &input[*i], nlen);
	if (!name)
		return (NULL);
	*i = *i + nlen;
	if (nlen == 1 && name[0] == '?')
		val = ft_itoa(shell->last_exit_status);
	else
	{
		env = ft_getenv(shell, name);
		// env = getenv(name);
		if (env)
			val = ft_track_strdup(shell, env);
		else
			val = ft_track_strdup(shell, "");
	}
	ft_track_free(shell, name);
	return (val);
}
typedef struct s_qbuf
{
	char	*buf;
	size_t	cap;
	size_t	len;
}	t_qbuf;

static int	grow_qbuf(t_qbuf *ctx, t_shell *shell)
{
	char	*tmp;
	size_t	newcap;

	newcap = ctx->cap * 2;
	tmp = ft_track_malloc(shell, newcap);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, ctx->buf, ctx->len);
	ft_track_free(shell, ctx->buf);
	ctx->buf = tmp;
	ctx->cap = newcap;
	return (1);
}

static int	emit_char(t_qbuf *ctx, t_shell *shell, const char c)
{
	if (ctx->len + 2 >= ctx->cap)
		if (!grow_qbuf(ctx, shell))
			return (0);
	ctx->buf[ctx->len] = c;
	ctx->len++;
	return (1);
}

static int	emit_str(t_qbuf *ctx, t_shell *shell, const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
	{
		if (!emit_char(ctx, shell, s[idx]))
			return (0);
		idx++;
	}
	return (1);
}

static int	process_double(t_qbuf *ctx, t_shell *shell, const char *input,
				size_t *i)
{
	char	*val;

	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			val = get_var_value(shell, input, i);
			if (!val || !emit_str(ctx, shell, val))
			{
				ft_track_free(shell, val);
				return (0);
			}
			ft_track_free(shell, val);
		}
		else
		{
			if (!emit_char(ctx, shell, input[*i]))
				return (0);
			(*i)++;
		}
	}
	if (input[*i] != '"')
	{
		ft_quote_error('"');
		return (0);
	}
	return (1);
}

static t_token	*finalize_double(t_shell *shell, t_qbuf *ctx, size_t *i)
{
	t_token	*tok;

	(*i)++;
	ctx->buf[ctx->len] = '\0';
	tok = ft_create_token(shell, TOKEN_WORD, ctx->buf, ctx->len);
	if (tok)
	{
		tok->glue = true;
		tok->quote_type = QUOTE_DOUBLE;
	}
	ft_track_free(shell, ctx->buf);
	return (tok);
}

static t_token *handle_double_quotes(t_shell *shell, const char *input,
				size_t *i)
{
	t_qbuf	ctx;

	ctx.cap = 64;
	ctx.len = 0;
	ctx.buf = ft_track_malloc(shell, ctx.cap);
	if (!ctx.buf)
		return (NULL);
	(*i)++;
	if (!process_double(&ctx, shell, input, i))
	{
		ft_track_free(shell, ctx.buf);
		return (NULL);
	}
	return (finalize_double(shell, &ctx, i));
}

static t_token	*handle_single_quotes(t_shell *shell, const char *input,
				size_t *i)
{
	size_t	start;
	size_t	len;
	t_token	*tok;

	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
	{
		ft_quote_error('\'');
		return (NULL);
	}
	len = *i - start;
	tok = ft_create_token(shell, TOKEN_WORD, &input[start], len);
	if (tok)
	{
		tok->glue = true;
		tok->quote_type = QUOTE_SINGLE;
	}
	(*i)++;
	return (tok);
}

t_token	*ft_handle_quotes(t_shell *shell, const char *input, size_t *i)
{
	if (input[*i] == '"')
		return handle_double_quotes(shell, input, i);
	return handle_single_quotes(shell, input, i);
}
