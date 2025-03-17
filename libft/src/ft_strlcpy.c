/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:37:54 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/17 13:37:57 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < size)
		ft_memcpy(dest, src, srclen +1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size -1);
		dest[size -1] = '\0';
	}
	return (srclen);
}
