/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_copy_args(t_shell *shell, t_command *cmd, t_ast_node *node)
{
	int	i;

	if (node->argc == 0)
		return (0);
	cmd->args = ft_track_malloc(shell, sizeof(char *) * (node->argc + 1));
	if (!cmd->args)
		return (1);
	i = 0;
	while (i < node->argc)
	{
		cmd->args[i] = ft_track_strdup(shell, node->args[i]);
		if (!cmd->args[i])
			return (1);
		i++;
	}
	cmd->args[i] = NULL;
	return (0);
}

t_command	*ft_ast_to_command(t_shell *shell, t_ast_node *node)
{
	t_command	*cmd;

	if (!node || node->type != AST_COMMAND)
		return (NULL);
	cmd = ft_init_cmd(shell);
	if (!cmd)
		return (NULL);
	if (node->argc > 0 && node->args)
	{
		cmd->cmdname = ft_track_strdup(shell, node->args[0]);
		if (ft_copy_args(shell, cmd, node) != 0)
			return (NULL);
		cmd->argsc = node->argc;
		cmd->envp = shell->envp;
	}
	return (cmd);
}

int	ft_open_redir_in(t_ast_node *node, t_command *cmd)
{
	cmd->fd_in = open(node->filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		ft_perror("minishell", node->filename, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_open_redir_out(t_ast_node *node, t_command *cmd)
{
	cmd->fd_out = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
	{
		ft_perror("minishell", node->filename, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_open_redir_append(t_ast_node *node, t_command *cmd)
{
	cmd->fd_out = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out == -1)
	{
		ft_perror("minishell", node->filename, strerror(errno));
		return (1);
	}
	return (0);
}
