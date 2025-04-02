/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:53:24 by sscholz           #+#    #+#             */
/*   Updated: 2024/08/21 18:53:27 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write_p(va_list args)
{
	uintptr_t	addr;
	void		*ptr;
	char		*hex_str;
	int			written;

	ptr = va_arg(args, void *);
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	addr = (uintptr_t)ptr;
	written = 0;
	hex_str = ft_itoa_hex(addr, 0);
	written += write(1, "0x", 2);
	written += write(1, hex_str, ft_strlen(hex_str));
	free(hex_str);
	return (written);
}

int	ft_write_hex(va_list args, int uppercase)
{
	unsigned int	num;
	char			*hex_str;
	int				written;

	num = va_arg(args, unsigned int);
	written = 0;
	hex_str = ft_itoa_hex(num, uppercase);
	written += write(1, hex_str, ft_strlen(hex_str));
	free(hex_str);
	return (written);
}
