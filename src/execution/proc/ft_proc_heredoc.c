/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/04 19:52:25 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	hd_read_loop(t_shell *shell, const char *dest, char **str,
				char **heredoc)
{
	char	*temp;

	while (1)
	{
		*str = readline(">");
		if (!(*str))
			break ;
		if (!ft_strcmp(*str, dest))
			break ;
		temp = ft_track_strjoin(shell, *heredoc, *str);
		free(*str);
		if (!temp)
		{
			ft_track_free(shell, *heredoc);
			exit(1);
		}
		ft_track_free(shell, *heredoc);
		*heredoc = ft_track_strjoin(shell, temp, "\n");
		if (!(*heredoc))
		{
			ft_track_free(shell, temp);
			exit(1);
		}
		ft_track_free(shell, temp);
	}
}

static char	*hd_read_input(t_shell *shell, const char *dest)
{
	char	*heredoc;
	char	*str;

	heredoc = ft_track_strdup(shell, "");
	if (!heredoc)
		exit(1);
	str = NULL;
	hd_read_loop(shell, dest, &str, &heredoc);
	if (str)
		free(str);
	return (heredoc);
}

static void	hd_run_child(t_shell *shell, int fdpipe[], const char *dest)
{
	char	*heredoc;
	int		ev;

	signal(SIGINT, SIG_DFL);
	close(fdpipe[0]);
	heredoc = hd_read_input(shell, dest);
	if (!heredoc)
		exit(1);
	ev = 0;
	if (write(fdpipe[1], heredoc, ft_strlen(heredoc)) == -1)
		ev = 1;
	close(fdpipe[1]);
	ft_free_all_tracked(shell);
	exit(ev);
}

static int	read_heredoc(t_shell *shell, t_command *cmd, const char *dest)
{
	int		fdpipe[2];
	pid_t	pid;
	int		status;

	if (pipe(fdpipe) == -1)
	{
		ft_perror("minishell", "HereDoc", strerror(errno));
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		hd_run_child(shell, fdpipe, dest);
	}
	close(fdpipe[1]);
	if (waitpid(pid, &status, 0) == -1)
		ft_perror("minishell", "HereDoc", strerror(errno));
	if (WIFEXITED(status))
		cmd->exit_val = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		cmd->exit_val = 128 + WTERMSIG(status);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
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
	fd = read_heredoc(shell, cmd, token->value);
	if (fd == -1)
	{
		cmd->exit_val = 1;
		return (NULL);
	}
	if (cmd->fd_in != STDIN_FILENO && close(cmd->fd_in) == -1)
	{
		ft_perror("minishell", "HereDoc", strerror(errno));
		cmd->exit_val = 1;
		close(fd);
		return (NULL);
	}
	cmd->fd_in = fd;
	return (token->next);
}
