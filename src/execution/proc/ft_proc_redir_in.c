/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_redir_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 12:16:25 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static int	check_token_type(t_token *token, t_command *cmd)
{
	if (token->type != TOKEN_WORD)
	{
		ft_perror_syntax(token->value);
		cmd->exit_val = 2;
		return (1);
	}
	return (0);
}

static int	check_access(t_token *token, t_command *cmd)
{
	if (access(token->value, F_OK) == -1)
	{
		ft_perror("minishell", token->value, strerror(errno));
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}

static int	open_fd(t_token *token, t_command *cmd)
{
	int	fd;

	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		ft_perror("minishell", token->value, strerror(errno));
		if (cmd->prev)
			close(cmd->prev->fd_pipe[0]);
		cmd->exit_val = 1;
	}
	return (fd);
}

static int	close_current_fdin(t_command *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO && close(cmd->fd_out) == -1)
	{
		ft_perror("minishell", NULL, strerror(errno));
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}

t_token	*ft_process_redir_in(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;

	(void)shell;
	token = token->next;
	if (check_token_type(token, cmd))
		return (NULL);
	if (check_access(token, cmd))
		return (token->next);
	fd = open_fd(token, cmd);
	if (fd == -1)
		return (token->next);
	if (close_current_fdin(cmd))
	{
		close(fd);
		return (NULL);
	}
	cmd->fd_in = fd;
	return (token->next);
}
