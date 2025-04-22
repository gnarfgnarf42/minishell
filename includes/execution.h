/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:21:49 by nefimov           #+#    #+#             */
/*   Updated: 2025/04/22 17:46:37 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include "parser.h"

typedef struct s_command
{
	char 	*pathname;
	char 	**args;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		exit_val;
}	t_command;

void ft_exec_command(t_command *cmd);

#endif