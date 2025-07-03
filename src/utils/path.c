/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:45 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 14:34:25 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Check if str content '/' char. Return 1 if yes, 0 if no.
int	str_is_pathname(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	path_is_dir(char *path)
{
	struct stat	sb;

	if (access(path, F_OK) == 0 && stat(path, &sb) == 0)
		if (S_ISDIR(sb.st_mode))
			return (0);
	return (1);
}
