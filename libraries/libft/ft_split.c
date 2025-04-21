/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:58:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/26 17:34:12 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	ignore;

	count = 0;
	ignore = 0;
	while (*(s + ignore) != '\0')
	{
		if (*(s + ignore) == c)
			ignore++;
		else
		{
			count++;
			while (*(s + ignore) != '\0' && *(s + ignore) != c)
				ignore++;
		}
	}
	return (count);
}

static char	*write_word(char *given_word, char const *s,
		int index, int word_len)
{
	int	word_index;

	word_index = 0;
	while (word_len > 0)
	{
		*(given_word + word_index) = s[index - word_len];
		word_index++;
		word_len--;
	}
	*(given_word + word_index) = '\0';
	return (given_word);
}

static char	**free_mem(char **array, int number_of_words)
{
	while (number_of_words > 0)
	{
		number_of_words--;
		free(array[number_of_words]);
	}
	free(array);
	return (0);
}

char	**allocate_write_mem(char const *s, char c, char **array,
		int number_of_words)
{
	int	word_len;
	int	word_index;
	int	array_index;

	array_index = 0;
	word_index = 0;
	word_len = 0;
	while (array_index < number_of_words)
	{
		while (*(s + word_index) != '\0' && *(s + word_index) == c)
			word_index++;
		while (*(s + word_index) != '\0' && *(s + word_index) != c)
		{
			word_index++;
			word_len++;
		}
		*(array + array_index) = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!array)
			return (free_mem(array, array_index));
		write_word(*(array + array_index), s, word_index, word_len);
		array_index++;
		word_len = 0;
	}
	*(array + array_index) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_count;

	if (!s)
		return (0);
	word_count = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (0);
	array = allocate_write_mem(s, c, array, word_count);
	return (array);
}
