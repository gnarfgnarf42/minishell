/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:17:15 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/17 19:17:16 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_track_malloc(t_shell *shell, size_t size)
{
	t_track	*new_node;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);

	new_node = malloc(sizeof(t_track));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}

	new_node->ptr = ptr;
	new_node->size = size;
	new_node->next = shell->memory_list;
	shell->memory_list = new_node;
	return (ptr);
}

void	ft_track_free(t_shell *shell, void *ptr)
{
	t_track	*current;
	t_track	*prev;

	current = shell->memory_list;
	prev = NULL;
	if (!ptr)
		return ;

	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->memory_list = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_free_all_tracked(t_shell *shell)
{
	t_track	*current;
	t_track	*next;

	current = shell->memory_list;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	shell->memory_list = NULL;
}

char	*ft_track_strdup(t_shell *shell, const char *src)
{
	char	*dest;
	size_t	len;

	if (!src)
		return (NULL);

	len = ft_strlen(src) + 1;
	dest = ft_track_malloc(shell, len);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len);
	return (dest);
}
