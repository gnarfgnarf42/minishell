/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/01 22:37:22 by nefimov          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_pwd(t_shell *shell, t_command *cmd)
{
	char	*cwd;

	(void)shell;
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		ft_perror("minishell", "pwd", strerror(errno), 1);
		cmd->exit_val = 1;
		return (1);
	}
	if (write(STDOUT_FILENO, cwd, ft_strlen(cwd)) == -1
		|| write(STDOUT_FILENO, "\n", 1) == -1)
	{
		ft_perror("minishell", "pwd", strerror(errno), 1);
		cmd->exit_val = 1;
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
