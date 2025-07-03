/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:16:57 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 10:58:54 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Check identifire for valid syntaxis
static int	name_is_valid(char *s, int len)
{
	int	out;
	int	i;

	if (!s || len == 0)
		return (1);
	out = 0;
	i = 0;
	if (s[0] >= '0' && s[0] <= '9')
		return (1);
	while (i < len)
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (1);
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

// Searching in env string with identifier and set it's value
// Or create a new string in env
// Return 0 if Ok or 2 if error
static int	export_value(t_shell *shell, t_command *cmd, int eq_pos, char *arg)
{
	char	**env;
	char	*tmp;

	env = shell->envp;
	while (*env)
	{
		if (ft_strncmp(*env, arg, eq_pos) == 0 && (*env)[eq_pos] == '=')
		{
			tmp = *env;
			*env = ft_track_strdup(shell, arg);
			if (*env == NULL)
			{
				cmd->exit_val = 2;
				break ;
			}
			ft_track_free(shell, tmp);
			break ;
		}
		env++;
	}
	if (*env == NULL)
		if (add_line_to_envp(shell, arg) != 0)
			cmd->exit_val = 2;
	return (cmd->exit_val);
}

int	ft_export_arg(t_shell *shell, t_command *cmd, char *arg)
{
	int	eq_pos;
	int	i;

	eq_pos = -1;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	eq_pos = i;
	if (name_is_valid(arg, eq_pos) == 1)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		cmd->exit_val = 1;
	}
	else if (eq_pos >= 0 && (arg)[eq_pos] == 0)
		cmd->exit_val = 0;
	else
		cmd->exit_val = export_value(shell, cmd, eq_pos, arg);
	return (cmd->exit_val);
}

// Process each argument of cmd. First arg index is [1]
int	ft_ms_export(t_shell *shell, t_command *cmd)
{
	char	**arg;
	int		ret;

	arg = cmd->args;
	ret = 0;
	while (*(++arg))
	{
		if (ft_export_arg(shell, cmd, *arg))
			ret = 1;
	}
	cmd->exit_val = ret;
	return (cmd->exit_val);
}
