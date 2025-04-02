/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:26:14 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/29 18:26:23 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	len1;
	size_t	len2;
	char	*joint;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2 + 1;
	joint = (char *)malloc(total_len);
	if (joint == NULL)
		return (NULL);
	ft_memcpy(joint, s1, len1);
	ft_memcpy(joint + len1, s2, len2);
	joint[total_len - 1] = '\0';
	return (joint);
}
