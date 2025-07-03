/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:41:08 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/25 15:41:11 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	c;
	size_t	litlen;

	litlen = ft_strlen(little);
	c = *little;
	if (c == '\0')
		return ((char *)big);
	while (*big != '\0' && len >= litlen)
	{
		if (*big == c && ft_strncmp(big, little, litlen) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
