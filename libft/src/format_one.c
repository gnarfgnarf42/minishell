/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:53:09 by sscholz           #+#    #+#             */
/*   Updated: 2024/08/21 18:53:11 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write_c(va_list args)
{
	int		written;
	char	c;

	c = (char)va_arg(args, int);
	written = 0;
	written += write(1, &c, 1);
	return (written);
}

int	ft_write_s(va_list args)
{
	int		written;
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	written = 0;
	written += write(1, str, ft_strlen(str));
	return (written);
}

int	ft_write_d(va_list args)
{
	int		written;
	int		num;
	char	*str;

	num = va_arg(args, int);
	written = 0;
	str = ft_itoa(num);
	written += write(1, str, ft_strlen(str));
	free (str);
	return (written);
}

int	ft_write_u(va_list args)
{
	unsigned int	num;
	char			*str;
	int				written;

	num = (int)va_arg(args, unsigned int);
	written = 0;
	str = ft_itoa_unsigned(num);
	written += write(1, str, ft_strlen(str));
	free (str);
	return (written);
}
