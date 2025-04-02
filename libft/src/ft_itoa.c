/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:02:39 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/31 17:02:40 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_num_len(int n)
{
	size_t	len;
	long	num;

	num = n;
	len = 0;
	if (n <= 0)
		len = 1;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	num;
	int		sign;

	len = get_num_len(n);
	num = n;
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
		num = -num;
	while (len > 0)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
