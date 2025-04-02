/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:03:19 by sscholz           #+#    #+#             */
/*   Updated: 2024/08/22 17:03:22 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_num_len_unsigned(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char	*str;
	size_t	len;

	len = get_num_len_unsigned(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
