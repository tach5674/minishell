/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:27:32 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/17 16:54:34 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	skip_quoted_string(const char **str)
{
	char	quote;

	if (**str == '\'' || **str == '"')
	{
		quote = **str;
		(*str)++;
		while (**str && **str != quote)
			(*str)++;
		if (**str)
			(*str)++;
		return (true);
	}
	return (false);
}

int	count_words(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_whitespace(*str))
			str++;
		if (*str)
		{
			count++;
			skip_quoted_string(&str);
			while (*str && !is_whitespace(*str))
				if (!skip_quoted_string(&str))
					str++;
		}
	}
	return (count);
}

void	skip_quoted_string_and_count(const char **str, size_t *len)
{
	char	quote;

	if (**str == '\'' || **str == '"')
	{
		quote = **str;
		(*str)++;
		(*len)++;
		while (**str && **str != quote)
		{
			(*str)++;
			(*len)++;
		}
		if (**str)
		{
			(*str)++;
			(*len)++;
		}
	}
	else
	{
		(*str)++;
		(*len)++;
	}
}

char	*get_next_word(const char **str)
{
	const char	*start;
	char		*word;
	size_t		len;

	while (**str && is_whitespace(**str))
		(*str)++;
	start = *str;
	len = 0;
	while (**str && !is_whitespace(**str))
		skip_quoted_string_and_count(str, &len);
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}
