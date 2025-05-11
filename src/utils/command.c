/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:24:15 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/11 11:04:17 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_command	*ft_init_cmd(t_shell *shell)
{
	t_command	*cmd;

	cmd = (t_command *)ft_track_malloc(shell, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = ft_track_malloc(shell, sizeof(char *) * ARGS_MAX);
	if (!cmd->args)
		return (NULL);		
	cmd->cmdname = NULL;
	// cmd->args = NULL;
	cmd->argsc = 0;
	cmd->envp = NULL;
	cmd->exit_val = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->fd_pipe[1] = STDIN_FILENO;
	cmd->fd_pipe[0] = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

void		ft_free_cmd(t_shell *shell, t_command *cmd)
{
	if (cmd && cmd->args)
		ft_track_free(shell, cmd->args);
	if (cmd)
		ft_track_free(shell, cmd);
}
	
void		ft_print_cmd(t_command *cmd)
{
	char		**arg;

	arg = cmd->args;
	printf("\ncmd: '%s'\n", cmd->cmdname);
	printf("argsc: %d\nargs:", cmd->argsc);
	while (*arg)
	{
		if (arg != cmd->args)
			printf(",");
		printf(" '%s'", *arg);
		arg++;
	}
	printf("\nfd_in: %2d | fd_out: %d\n", cmd->fd_in, cmd->fd_out);
	printf("pipe: %3d | %d\n", cmd->fd_pipe[0], cmd->fd_pipe[1]);
	printf("next: %p\n", cmd->next);
	printf("\n");
}