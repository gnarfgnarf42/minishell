/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 00:19:52 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	ft_ms_env(t_shell *shell, t_command *cmd)
{
	(void)cmd;
	ft_penv(shell);
	return (0);
}

void	ft_penv(t_shell *shell)
{
	int	i;

	if (shell->envp == NULL)
		return ;
	i = 0;
	while (shell->envp[i])
	{
		write(STDOUT_FILENO, shell->envp[i], ft_strlen(shell->envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
