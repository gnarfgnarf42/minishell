/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:11:35 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/04 15:09:26 by nefimov          ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
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
	t_token					*tokens;
	t_track					*memory_list;
	t_command				*cmd_list;
	char					**envp;
	int						last_exit_status;
	int						is_interactive;
	bool					exit;
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

// Tokens functions
void	ft_print_tokens(t_token *tokens);
void	ft_check_empty_input(t_shell *shell, char *tracked_input);

// Envp functions
char	**ft_envp_cpy(t_shell *shell, char *envp[]);
char	*ft_getenv(t_shell *shell, char *name);

#endif