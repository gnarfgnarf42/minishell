/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 11:30:30 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	read_heredoc(const char *dest)
{
	char	*str;
	int		fdpipe[2];

	if (pipe(fdpipe) == -1)
	{
		ft_perror("minishell", "HereDoc", strerror(errno), 1);
		return (-1);
	}
	while (1)
	{
		str = readline(">");
		if (!ft_strcmp(str, dest))
			break ;
		write(fdpipe[1], str, ft_strlen(str));
		write(fdpipe[1], "\n", 1);
		free(str);
	}
	free(str);
	close(fdpipe[1]);
	return (fdpipe[0]);
}

t_token	*ft_process_heredoc(t_shell *shell, t_token *token, t_command *cmd)
{
	int	fd;

	(void)shell;
	token = token->next;
	if (token->type != TOKEN_WORD)
	{
		ft_perror_syntax(token->value);
		cmd->exit_val = 2;
		return (NULL);
	}
	fd = read_heredoc(token->value);
	if (fd == -1)
	{
		cmd->exit_val = 1;
		return (NULL);
	}
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
	{
		ft_perror("minishell", "HereDoc", strerror(errno), 1);
		cmd->exit_val = 1;
		close(fd);
		return (NULL);
	}
	cmd->fd_in = fd;
	return (token->next);
}
