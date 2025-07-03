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
# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef struct s_token		t_token;
typedef struct s_command	t_command;

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
	t_token	*tokens;
	t_track	*memory_list;
	int		last_exit_status;
}	t_shell;

// Memory functions
void	*ft_track_malloc(t_shell *shell, size_t size);
void	ft_track_free(t_shell *shell, void *ptr);
void	ft_free_all_tracked(t_shell *shell);
char	*ft_track_strdup(t_shell *shell, const char *src);
char	*ft_track_strndup(t_shell *shell, const char *s, size_t n);
char	*ft_track_strjoin(t_shell *shell, const char *s1, const char *s2);

// Main loop function
void	ft_minishell_loop(t_shell *shell);

#endif