/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:35 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/17 19:11:40 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/includes/libft.h"

// Memory tracking struct
typedef struct s_track
{
	void			*ptr;
	size_t			size;
	struct s_track	*next;
}	t_track;

// Shell state struct
typedef struct s_shell
{
	t_track	*memory_list;
}	t_shell;

// Memory functions
void	*ft_track_malloc(t_shell *shell, size_t size);
void	ft_track_free(t_shell *shell, void *ptr);
void	ft_free_all_tracked(t_shell *shell);
char	*ft_track_strdup(t_shell *shell, const char *src);

// Main loop function
void	ft_minishell_loop(t_shell *shell);

#endif