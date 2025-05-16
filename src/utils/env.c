/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:30:44 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 12:57:02 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static void	*clear_envp(t_shell *shell, char **envp)
{
	int	i;
	
	i = -1;
	while (envp[++i])
		ft_track_free(shell, envp[i]);
	return (NULL);
}

char	**ft_envp_cpy(t_shell *shell, char *envp[])
{
	int		i;
	int		c;
	char	**envp_cpy;

	if (envp == NULL)
		return (NULL);
	
	c = 0;
	while (envp[c])
		c++;	
	envp_cpy = (char **)ft_track_malloc(shell, (c + 1) * sizeof(char *));
	if (envp_cpy == NULL)
		return (NULL);
	
	i = -1;
	while (++i < c)
	{
		envp_cpy[i] = ft_track_strdup(shell, envp[i]);
		if (envp_cpy[i] == NULL)
			return (clear_envp(shell, envp_cpy));		
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
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

char	*ft_getenv(t_shell *shell, char *name)
{
	int		i;
	size_t 	j;
	size_t	name_len;
	
	if (shell->envp == NULL || name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	i = -1;
	while (shell->envp[++i])
	{
		j = 0;
		while(shell->envp[i][j] != '=' && shell->envp[i][j])
			j++;
		if (shell->envp[i][j] == '=')
			if (name_len == j && ft_strncmp(name, shell->envp[i], j) == 0)
				return (shell->envp[i] + j + 1);
	}
	return (NULL);
}


