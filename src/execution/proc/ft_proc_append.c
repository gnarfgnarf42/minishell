/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 11:47:36 by nefimov          ###   ########.fr       */
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

static int	open_fd(t_token *token, t_command *cmd)
{
	int	fd;

	fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_perror("minishell", token->value, strerror(errno), 1);
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
		ft_perror("minishell", NULL, strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}

t_token	*ft_process_append(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;

	(void)shell;
	token = token->next;
	if (check_token_type(token, cmd))
		return (NULL);
	fd = open_fd(token, cmd);
	if (fd == -1)
		return (token->next);
	if (close_current_fdin(cmd))
	{
		close(fd);
		return (NULL);
	}
	cmd->fd_out = fd;
	return (token->next);
}
