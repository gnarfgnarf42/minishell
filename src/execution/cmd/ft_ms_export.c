/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 18:31:22 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Find position of char '=' in string name
// Return position value or 0 if there are no '=' in name
// or it is in the begginig of the string
static int	find_eq_position(char *name)
{
	int	pos;
	int	i;

	if (!name)
		return (0);
	pos = 0;
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (name[i])
		pos = i;
	return (pos);
}

static int	name_is_valid(char *s, int len)
{
	int	out;
	int	i;

	out = 0;
	i = 0;
	while (i < len)
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			out = 1;
		i++;
	}
	return (out);
}

static int	add_line_to_envp(t_shell *shell, char *line)
{
	char	**new_envp;
	char	**tmp_envp;
	int		len;
	int		i;

	len = 0;
	while (shell->envp[len])
		len++;
	new_envp = (char **)ft_track_malloc(shell, (len + 2) * sizeof(char *));
	if (new_envp == NULL)
		return (1);
	i = -1;
	while (++i < len)
		new_envp[i] = shell->envp[i];
	new_envp[i] = ft_track_strdup(shell, line);
	if (new_envp[i] == NULL)
	{
		ft_track_free(shell, new_envp);
		return (1);
	}
	new_envp[i + 1] = NULL;
	tmp_envp = shell->envp;
	shell->envp = new_envp;
	ft_track_free(shell, tmp_envp);
	return (0);
}

int	ft_ms_export(t_shell *shell, t_command *cmd)
{
	char	**arg;
	char	**env;
	char	*tmp;
	int		eq_pos;
	int		out;

	if (shell == NULL || cmd == NULL)
		return (2);
	out = 0;
	arg = cmd->args;
	while (*(++arg))
	{
		eq_pos = find_eq_position(*arg);
		if (eq_pos == 0)
			continue ;
		if (name_is_valid(*arg, eq_pos) == 1)
		{
			ft_putstr_fd("-minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(*arg, STDERR_FILENO);
			ft_putstr_fd(" :not a valid identifier\n", STDERR_FILENO);
			cmd->exit_val = 1;
			out = 1;
			continue ;
		}
		env = shell->envp;
		while (*env)
		{
			if (ft_strncmp(*env, *arg, eq_pos) == 0 && (*env)[eq_pos] == '=')
			{
				tmp = *env;
				*env = ft_track_strdup(shell, *arg);
				if (*env == NULL)
				{
					cmd->exit_val = 2;
					out = 2;
					break ;
				}
				ft_track_free(shell, tmp);
				break ;
			}
			env++;
		}
		if (*env == NULL)
		{
			if (add_line_to_envp(shell, *arg) != 0)
			{
				cmd->exit_val = 2;
				out = 2;
			}
		}
	}
	return (out);
}
