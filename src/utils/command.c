/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:24:15 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/09 19:27:36 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

void	ft_print_cmd(t_command *cmd)
{
	char		**arg;

	arg = cmd->args;
	printf("\ncmd: '%s'\n", cmd->cmdname);
	printf("argsc: %d\nargs: ", cmd->argsc);
	while (*arg)
	{
		printf("'%s', ", *arg);
		arg++;
	}
	printf("\n");
}