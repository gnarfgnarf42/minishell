/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 12:15:08 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

#define PWD		"PWD="
#define OLD_PWD	"OLDPWD="
#define HOME	"HOME"

static char	*get_path(t_shell *shell, t_command *cmd)
{
	char	*path;

	path = ft_getenv(shell, HOME);
	if (cmd->argsc == 1 && path == NULL)
	{
		ft_perror("minishell", "cd", "HOME variable not found");
		cmd->exit_val = 1;
		return (NULL);
	}
	else if (cmd->argsc > 2)
	{
		ft_perror("minishell", "cd", "too many arguments");
		cmd->exit_val = 1;
		return (NULL);
	}
	else if (cmd->argsc == 2)
		path = cmd->args[1];
	return (path);
}

static int	make_env_line(t_command *cmd, char *ident, char *line)
{
	size_t	str_len;

	str_len = ft_strlen(ident);
	ft_memcpy(line, ident, str_len + 1);
	if (getcwd(line + str_len, PATH_MAX - str_len) == NULL)
	{
		ft_perror("minishell", "cd", strerror(errno));
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}

int	ft_ms_cd(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];

	path = get_path(shell, cmd);
	if (path == NULL)
		return (1);
	if (make_env_line(cmd, OLD_PWD, old_pwd))
		return (1);
	if (chdir(path) == -1)
	{
		ft_perror("minishell", "cd", strerror(errno));
		cmd->exit_val = 1;
		return (1);
	}
	if (make_env_line(cmd, PWD, pwd))
		return (1);
	if (ft_export_arg(shell, cmd, old_pwd) || ft_export_arg(shell, cmd, pwd))
	{
		ft_perror("minishell", "cd", strerror(errno));
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}
