/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:36:12 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/16 19:36:15 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned int		i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = dest;
	s = src;
	if (dest == 0 && src == 0)
		return (dest);
	while (i < num)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
