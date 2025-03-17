/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:25:29 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/17 19:25:35 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (str1[i] == '\0' || str2[i] == '\0' || str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
