/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 17:48:51 by nefimov          ###   ########.fr       */
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
	arg = cmd->args;
	while (*(++arg))
	{
		env = shell->envp;
		while (*env)
		{
			if (ft_strncmp(*env, *arg, ft_strlen(*arg)) == 0
				&& (*env)[ft_strlen(*arg)] == '=')
			{
				tmp = *env;
				while (*env)
				{
					*env = *(env + 1);
					env = env + 1;
				}
				ft_track_free(shell, tmp);
				break ;
			}
			env++;
		}
	}
	return (out);
}
