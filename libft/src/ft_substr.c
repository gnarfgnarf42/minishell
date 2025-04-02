/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:37:24 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/29 17:45:44 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*create_empty_string(void)
{
	char	*empty_str;

	empty_str = (char *)malloc(1);
	if (empty_str)
		empty_str[0] = '\0';
	return (empty_str);
}

static void	copy_substr(char *substr, const char *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*substr;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (create_empty_string());
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	copy_substr(substr, s, start, len);
	return (substr);
}
