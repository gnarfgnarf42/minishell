/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:09:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/04/29 19:36:45 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	full_path = ft_track_malloc(shell, cur_len + ft_strlen(cmd->pathname) + 2);
	if (!full_path)
		return (NULL);
	i = -1;	
	while (cur_path[++i])
		full_path[i] = cur_path[i];
	if (cur_len > 0 && cur_path[cur_len - 1] != '/')
		full_path[i++] = '/';
	j = 0;
	while (cmd->pathname[j])
		full_path[i++] = cmd->pathname[j++];
	full_path[i] = 0;
	return full_path;
}

int	path_is_dir(char *path)
{
	struct stat	sb;

	if (access(path, F_OK) == 0 && stat(path, &sb) == 0)
		if (S_ISDIR(sb.st_mode))
			return (0);
	return (1);
}

// Search execution file with name "cmd->pathname" in directories
// stored in env. variable PATH
// Return 0 and save pesult path to the "cmd->pathname"
// Return 1 and print error if no file, PATH variable or error
int search_in_path(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	*cur_path;
	char	*full_path;

	path = getenv(PATH_ENV);
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
			// ft_track_free(shell, cmd->pathname);
			cmd->pathname = full_path;
			return (0);	
		}
		ft_track_free(shell, full_path);
		cur_path = get_next_path(NULL, PATH_DELIMITER);
	}
	ft_track_free(shell, path);
	return (1);
}

// Check if str content '/' char. Return 1 if yes, 0 if no.
int str_is_pathname(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

// Get a path for command name in cmd->pathname 
// If cmd->pathname is a path (consist '/') return 0;
// If cmd->pathname is not a path, searc it in PATH variable
int	ft_get_path(t_shell *shell, t_command *cmd)
{
	// Check if cmd->pathname is a path
	if (str_is_pathname(cmd->pathname) == 1 && access(cmd->pathname, F_OK) == 0)
		return (0);
	// Get pathnames from PATH env variable and check it for exist
	if (search_in_path(shell, cmd) == 0)
		return (0);
	return (1);
}
