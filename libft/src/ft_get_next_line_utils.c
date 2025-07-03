/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:23 by nefimov           #+#    #+#             */
/*   Updated: 2025/07/02 16:02:37 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
#include "libft.h"

/*
	Create a new string, that is a result of concatination of string 's1'
	and 'size' bites of string 's2'. Set copied bytes of 's2' to '\0'.
	Free allocated memory of string 's1' in the end.

	INPUT: strings 's1', 's2' and number of bytes 'size' to copy from 's2'
	RETURN: string 's' or NULL if error
*/
char	*ft_strljoin(char *s1, char *s2, size_t size)
{
	char	*s;
	char	*s_iter;
	char	*s1_to_free;

	s1_to_free = s1;
	s = (char *) malloc((ft_strlen(s1) + size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s_iter = s;
	while (*s1)
	{
		*s_iter++ = *s1;
		s1++;
	}
	while (size > 0)
	{
		*s_iter++ = *s2;
		*s2 = '\0';
		s2++;
		size--;
	}
	*s_iter = '\0';
	free(s1_to_free);
	return (s);
}

/* 	Create a zero string or NULL if error */
char	*alloc_zero(void)
{
	char	*p;

	p = (char *) malloc(1);
	if (p == NULL)
		return (NULL);
	*p = '\0';
	return (p);
}

/*
	Return index of the first non '\0' element in char array 'buff'.
	If all elements are '\0' make a new read. 


	INPUT:  char buffer 'buff' of size BUFFER_SIZE and file descriptor 'fd'.
	RETURN: index 'i' of the first non '\0' element in char array 'buff'
			or '-1' if error or end of the file was reached.
*/
int	check_init_buff(char *buff, ssize_t	fd)
{
	ssize_t	i;
	ssize_t	rd;

	if (fd < 0)
		return (-1);
	i = 0;
	while (buff[i] == 0 && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1 || rd == 0)
			return (-1);
		i = 0;
	}
	return (i);
}

/*
	Read a next line from the file descriptor <fd>.
	Keep readed buffer in static var <buff>.

	INPUT:  index <i> of first element to read in <buff>;
		    file descriptor <fd>. 
	RETURN: readed string <str> or NULL in cause of error,
		    or if the end of the file was reached.
*/
char	*read_new_line(ssize_t	i, char *buff, ssize_t	fd)
{
	char	*str;
	ssize_t	start;
	ssize_t	rd;

	start = i;
	str = alloc_zero();
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		if (++i == BUFFER_SIZE)
		{
			str = ft_strljoin(str, &buff[start], BUFFER_SIZE - start);
			rd = read(fd, buff, BUFFER_SIZE);
			if (rd == -1 || rd == 0)
			{
				if (*str)
					return (str);
				free(str);
				return (NULL);
			}
			i = 0;
			start = i;
		}
	}
	str = ft_strljoin(str, &buff[start], (i - start + 1));
	return (str);
}
