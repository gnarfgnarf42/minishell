/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by sscholz           #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_exec_redir(t_shell *shell, t_ast_node *node, t_command *cmd)
{
	(void)shell;
	if (node->type == AST_REDIR_IN)
		return (ft_open_redir_in(node, cmd));
	else if (node->type == AST_REDIR_OUT)
		return (ft_open_redir_out(node, cmd));
	else if (node->type == AST_REDIR_APPEND)
		return (ft_open_redir_append(node, cmd));
	return (0);
}

static int	ft_exec_pipe_ast(t_shell *shell, t_ast_node *node)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		ft_exec_pipe_left(shell, node, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		ft_exec_pipe_right(shell, node, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}

static int	ft_exec_command_node(t_shell *shell, t_command *cmd)
{
	int	status;

	shell->cmd_list = cmd;
	ft_set_cmd_builtin(shell);
	if (cmd->is_builtin)
		status = ft_exec_builtin(shell, cmd);
	else
	{
		if (ft_get_path(shell, cmd) == 0)
			status = ft_exec_external(shell, cmd);
		else
			status = 127;
	}
	if (cmd->pid > 0)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	ft_free_cmd_line(shell);
	return (status);
}

static int	ft_exec_redir_node(t_shell *shell, t_ast_node *node)
{
	t_command	*cmd;

	cmd = ft_ast_to_command(shell, node->left);
	if (!cmd)
		return (1);
	if (ft_exec_redir(shell, node, cmd) != 0)
	{
		ft_free_cmd(shell, cmd);
		return (1);
	}
	return (ft_exec_command_node(shell, cmd));
}

int	ft_exec_ast_node(t_shell *shell, t_ast_node *node)
{
	t_command	*cmd;

	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (ft_exec_pipe_ast(shell, node));
	else if (node->type == AST_COMMAND)
	{
		cmd = ft_ast_to_command(shell, node);
		if (!cmd)
			return (1);
		return (ft_exec_command_node(shell, cmd));
	}
	else if (node->type >= AST_REDIR_IN && node->type <= AST_REDIR_HEREDOC)
		return (ft_exec_redir_node(shell, node));
	return (0);
}
