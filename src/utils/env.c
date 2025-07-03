/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:30:44 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 00:19:45 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

static size_t	get_num_len(int n)
{
	size_t	len;
	long	num;

	num = n;
	len = 0;
	if (n <= 0)
		len = 1;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_track_itoa(t_shell *shell, int n)
{
	char	*str;
	size_t	len;
	long	num;
	int		sign;

	len = get_num_len(n);
	num = n;
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	str = (char *)ft_track_malloc(shell, (len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
		num = -num;
	while (len > 0)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

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
	int		count;
	char	**envp_cpy;

	if (envp == NULL)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	envp_cpy = (char **)ft_track_malloc(shell, (count + 1) * sizeof(char *));
	if (envp_cpy == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		envp_cpy[i] = ft_track_strdup(shell, envp[i]);
		if (envp_cpy[i] == NULL)
			return (clear_envp(shell, envp_cpy));
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}

char	*ft_getenv(t_shell *shell, char *name)
{
	int		i;
	size_t	j;
	size_t	name_len;

	if (shell->envp == NULL || name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	if (name_len == 1 && name[0] == '?')
		return (ft_track_itoa(shell, shell->last_exit_status));
	i = -1;
	while (shell->envp[++i])
	{
		j = 0;
		while (shell->envp[i][j] != '=' && shell->envp[i][j])
			j++;
		if (shell->envp[i][j] == '=')
			if (name_len == j && ft_strncmp(name, shell->envp[i], j) == 0)
				return (shell->envp[i] + j + 1);
	}
	return (NULL);
}
