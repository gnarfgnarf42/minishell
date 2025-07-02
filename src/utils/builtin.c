/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:59:17 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/03 00:01:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

// Check if cmdname is a build-in function
// Return 0 if yes and execution is success
// Return -1 if yes and execution with error
// Return 1 if cmdname is not a build-in function
int	ft_exec_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (!ft_strcmp(cmd->cmdname, "echo"))
		return (ft_ms_echo(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "cd"))
		return (ft_ms_cd(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "pwd"))
		return (ft_ms_pwd(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "export"))
		return (ft_ms_export(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "unset"))
		return (ft_ms_unset(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "env"))
		return (ft_ms_env(shell, cmd));
	else if (!ft_strcmp(cmd->cmdname, "exit"))
		return (ft_ms_exit(shell, cmd));
	return (1);
}

int	ft_cmd_is_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (!ft_strcmp(cmd->cmdname, "echo"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "cd"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "pwd"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "export"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "unset"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "env"))
		cmd->is_builtin = 1;
	else if (!ft_strcmp(cmd->cmdname, "exit"))
		cmd->is_builtin = 1;
	return (cmd->is_builtin);
}
