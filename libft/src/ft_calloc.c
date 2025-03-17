/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:16:47 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/29 15:42:30 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;
	size_t	max_size_t;

	max_size_t = (size_t) - 1;
	if (nmemb == 0 || size == 0)
		total_size = 0;
	else
	{
		if (nmemb > max_size_t / size)
			return (NULL);
		total_size = nmemb * size;
	}
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
