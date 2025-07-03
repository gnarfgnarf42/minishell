/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:58:24 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/16 19:58:29 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned int		i;

	s = src;
	d = dest;
	if (d < s)
	{
		i = 0;
		while (i < num)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		i = num;
		while (i > 0)
		{
			d[i -1] = s[i -1];
			i--;
		}
	}
	return (dest);
}
