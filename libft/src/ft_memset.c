/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:49:55 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/16 17:54:00 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*data;
	unsigned int	i;

	i = 0;
	data = ptr;
	while (i < num)
	{
		data[i] = value;
		i++;
	}
	return (ptr);
}
