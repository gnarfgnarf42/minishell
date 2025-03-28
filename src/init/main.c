/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:34 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/17 19:22:37 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	main(void)
{
	t_shell	shell;

	shell.tokens = NULL;
	shell.memory_list = NULL;
	ft_minishell_loop(&shell);
	return (0);
}
