/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:58:10 by sscholz           #+#    #+#             */
/*   Updated: 2024/04/17 18:58:12 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	uc;
	const char		*last_occurence;

	last_occurence = NULL;
	uc = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == uc)
			last_occurence = str;
		str++;
	}
	if (uc == 0)
		return ((char *)str);
	return ((char *)last_occurence);
}
