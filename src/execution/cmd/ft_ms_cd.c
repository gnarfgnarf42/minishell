/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/30 14:19:40 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

#define PWD	"PWD"
#define OLD_PWD	"OLDPWD"

int	ft_ms_cd(t_shell *shell, t_command *cmd)
{
	char	*path;

	(void)shell;
	path = getenv("HOME");
	if (cmd->argsc == 1 && path == NULL)
	{
		write(STDERR_FILENO, "-minishell: cd: HOME variable not found\n", 35);
		cmd->exit_val = 1;
		return (1);
	}
	else if (cmd->argsc == 2)
		path = cmd->args[1];
	else if (cmd->argsc > 2)
	{
		write(STDERR_FILENO, "-minishell: cd: too many arguments\n", 35);
		cmd->exit_val = 1;
		return (1);
	}
	if (!path || chdir(path) == -1)
	{
		perror("-minishell: cd");
		cmd->exit_val = 1;
		return (1);
	}
	/* else
	{
		ft_ms_export();
	} */
	return (0);
}
