/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:56:11 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/29 18:56:16 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_in_set(char c, const char *set)
{
	return (ft_strchr(set, c) != NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed_str;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && is_in_set(*start, set))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && is_in_set(*(end - 1), set))
		end--;
	len = end - start;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, start, len + 1);
	return (trimmed_str);
}
