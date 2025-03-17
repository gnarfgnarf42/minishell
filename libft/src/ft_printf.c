/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:37:17 by sscholz           #+#    #+#             */
/*   Updated: 2024/08/18 19:37:21 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		total_written;
	int		i;

	va_start(args, string);
	total_written = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			total_written += ft_format(string[i + 1], args);
			i++;
		}
		else
			total_written += write(1, &string[i], 1);
		i++;
	}
	va_end(args);
	return (total_written);
}

int	ft_format(char specifier, va_list args)
{
	int	written;

	written = 0;
	if (specifier == 'c')
		written += ft_write_c(args);
	else if (specifier == 's')
		written += ft_write_s(args);
	else if (specifier == 'p')
		written += ft_write_p(args);
	else if (specifier == 'd' || specifier == 'i')
		written += ft_write_d(args);
	else if (specifier == 'u')
		written += ft_write_u(args);
	else if (specifier == 'x')
		written += ft_write_hex(args, 0);
	else if (specifier == 'X')
		written += ft_write_hex(args, 1);
	else if (specifier == '%')
		written += write(1, "%", 1);
	return (written);
}
