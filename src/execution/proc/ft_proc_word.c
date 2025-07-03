/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:02:41 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/16 18:48:23 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_token	*ft_process_word(t_shell *shell, t_token *token, t_command *cmd)
{
	(void)shell;
	if (cmd->cmdname == NULL)
		cmd->cmdname = token->value;
	cmd->args[cmd->argsc] = token->value;
	cmd->argsc += 1;
	cmd->args[cmd->argsc] = NULL;
	return (token->next);
}
