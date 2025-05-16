/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 17:14:50 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_unset(t_shell *shell, t_command *cmd)
{
	char	**arg;
	char	**env;
	char	*tmp;
	int		out;
	
	if (shell == NULL || cmd == NULL)
		return (2);
	out = 0;
	// for each arg
	arg = cmd->args;
	while (*(++arg))
	{
		// Try to find name in env
		env = shell->envp;
		while (*env)
		{
			// If name is in env, remove the line
			if (ft_strncmp(*env, *arg, ft_strlen(*arg)) == 0 && (*env)[ft_strlen(*arg)] == '=')
			{
				tmp = *env;
				while (*env)
				{
					*env = *(env + 1);
					env = env + 1;
				}
				ft_track_free(shell, tmp);
				break;
			}
			env++;
		}
	}
	// if (write(STDOUT_FILENO, "export\n", 7) == -1)
	// {
	// 	perror("-minishell");
	// 	cmd->exit_val = 1;
	// 	return (-1);
	// }
	return (out);
}