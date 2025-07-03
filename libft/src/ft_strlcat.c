/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:09:24 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/17 16:09:26 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_end_of_dest(char *dest, size_t size)
{
	while (size-- != 0 && *dest != '\0')
		dest++;
	return (dest);
}

static void	copy_src_to_dest(char **d, const char **s, size_t *n)
{
	while (**s != '\0')
	{
		if (*n != 1)
		{
			**d = **s;
			(*d)++;
			(*n)--;
		}
		(*s)++;
	}
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		dlen;

	d = find_end_of_dest(dest, size);
	dlen = d - dest;
	n = size - dlen;
	if (n == 0)
		return (dlen + ft_strlen(src));
	s = src;
	copy_src_to_dest(&d, &s, &n);
	*d = '\0';
	return (dlen + (s - src));
}
