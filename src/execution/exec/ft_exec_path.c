/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:09:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/04 19:24:53 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

// Additional checks for null strings can be added
char	*get_next_path(char *path, char delim)
{
	static char	*next_path;
	char		*out;

	if (path)
		next_path = path;
	else
	{
		if (*next_path == 0)
			return (NULL);
		path = next_path;
	}
	while (*path != 0 && *path != delim)
		path++;
	if (*path == delim)
	{
		out = next_path;
		next_path = path + 1;
		*path = 0;
	}
	else
	{
		out = next_path;
		next_path = path;
	}
	return (out);
}

char	*get_full_path(t_shell *shell, t_command *cmd, char *cur_path)
{
	int		i;
	int		j;
	char	*full_path;
	int		cur_len;

	if (!cur_path)
		return (NULL);
	cur_len = ft_strlen(cur_path);
	full_path = ft_track_malloc(shell, cur_len + ft_strlen(cmd->cmdname) + 2);
	if (!full_path)
		return (NULL);
	i = -1;
	while (cur_path[++i])
		full_path[i] = cur_path[i];
	if (cur_len > 0 && cur_path[cur_len - 1] != '/')
		full_path[i++] = '/';
	j = 0;
	while (cmd->cmdname[j])
		full_path[i++] = cmd->cmdname[j++];
	full_path[i] = 0;
	return (full_path);
}

// Search execution file with name "cmd->pathname" in directories
// stored in env. variable PATH
// Return 0 and save pesult path to the "cmd->pathname"
// Return 1 and print error if no file, PATH variable or error
int	search_in_path(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	*cur_path;
	char	*full_path;

	path = ft_getenv(shell, PATH_ENV);
	if (path == NULL)
		return (1);
	path = ft_track_strdup(shell, path);
	cur_path = get_next_path(path, PATH_DELIMITER);
	while (cur_path)
	{
		full_path = get_full_path(shell, cmd, cur_path);
		if (!full_path)
			return (2);
		if (access(full_path, F_OK) == 0 && path_is_dir(full_path) != 0)
		{
			cmd->cmdname = full_path;
			return (0);
		}
		ft_track_free(shell, full_path);
		cur_path = get_next_path(NULL, PATH_DELIMITER);
	}
	ft_track_free(shell, path);
	return (1);
}

// Get a path for command name in cmd->pathname 
// If cmd->pathname is a path (consist '/') return 0;
// If cmd->pathname is not a path, searc it in PATH variable
int	ft_get_path(t_shell *shell, t_command *cmd)
{
	if (str_is_pathname(cmd->cmdname))
	{
		if (!path_is_dir(cmd->cmdname))
		{
			ft_perror("minishell", cmd->args[0], "Is a directory");
			cmd->exit_val = 126;
			return (2);
		}
		if (access(cmd->cmdname, F_OK))
		{
			ft_perror("minishell", cmd->args[0], "No such file or directory");
			cmd->exit_val = 127;
			return (1);
		}
	}
	else if (search_in_path(shell, cmd))
	{
		ft_perror("minishell", cmd->args[0], "command not found");
		cmd->exit_val = 127;
		return (1);
	}
	return (0);
}
