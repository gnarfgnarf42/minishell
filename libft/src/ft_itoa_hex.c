/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:05:35 by sscholz           #+#    #+#             */
/*   Updated: 2024/08/21 20:05:37 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static size_t	get_num_len(uintptr_t n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

char	*ft_itoa_hex(uintptr_t num, int uppercase)
{
	size_t	len;
	char	*str;
	char	base;

	if (uppercase)
		base = 'A';
	else
		base = 'a';
	if (num == 0)
		return (ft_strdup("0"));
	len = get_num_len(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		if ((num % 16) < 10)
			str[--len] = (num % 16) + '0';
		else
			str[--len] = (num % 16) - 10 + base;
		num = num / 16;
	}
	return (str);
}
