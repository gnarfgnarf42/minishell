/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:09:53 by sscholz           #+#    #+#             */
/*   Updated: 2024/05/31 13:09:56 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static void	free_split(char **split, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *s, size_t start, size_t finish)
{
	char	*word;
	size_t	i;

	word = (char *)malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	split_words(const char *s, char c, char **split)
{
	size_t	i;
	size_t	j;
	int		start;

	i = -1;
	j = 0;
	start = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			split[j] = word_dup(s, start, i);
			if (!split[j])
			{
				free_split(split, j);
				return (0);
			}
			j++;
			start = -1;
		}
	}
	split[j] = (NULL);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**split;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (!split_words(s, c, split))
		return (NULL);
	return (split);
}
