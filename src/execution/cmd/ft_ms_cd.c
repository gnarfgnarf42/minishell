/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 23:56:32 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

#define PWD	"PWD="
#define OLD_PWD	"OLDPWD="

int	ft_ms_cd(t_shell *shell, t_command *cmd)
{
	char	*path;
	char 	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];

	(void)shell;
	path = ft_getenv(shell, "HOME");
	if (cmd->argsc == 1 && path == NULL)
	{
		ft_perror("minishell", "cd", "HOME variable not found", 1);
		cmd->exit_val = 1;
		return (1);
	}
	else if (cmd->argsc > 2)
	{
		ft_perror("minishell", "cd", "too many arguments", 1);
		cmd->exit_val = 1;
		return (1);
	}
	else if (cmd->argsc == 2)
		path = cmd->args[1];

	// Fill string pwd in format 'OLDPWD=<path>'
	ft_memcpy(old_pwd, OLD_PWD, ft_strlen(OLD_PWD) + 1);
	if (getcwd(old_pwd + ft_strlen(OLD_PWD), PATH_MAX - ft_strlen(OLD_PWD)) == NULL)
	{
		ft_perror("minishell", "cd", strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}

	// Change pwd
	if (chdir(path) == -1)
	{
		ft_perror("minishell", "cd", strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}

	// Fill string pwd in format 'PWD=<path>'
	ft_memcpy(pwd, PWD, ft_strlen(PWD) + 1);
	if (getcwd(pwd + ft_strlen(PWD), PATH_MAX - ft_strlen(PWD)) == NULL)
	{
		ft_perror("minishell", "cd", strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}

	// Export old_pwd and pwd to env
	if (ft_export_arg(shell, cmd, old_pwd) || ft_export_arg(shell, cmd, pwd))
	{
		ft_perror("minishell", "cd", strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}
	return (0);
}
