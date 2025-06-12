/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:51:06 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 17:59:14 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quote(char **str, int i, int *in_quotes)
{
	char	*temp;
	char	*temp1;
	int		check;

	if ((*str)[i] == '\'')
		check = 1;
	else
		check = 2;
	if (*in_quotes != (3 - check))
	{
		temp = ft_strndup(*str, i);
		if (!temp)
			return (-1);
		temp1 = ft_strjoin(temp, *str + i + 1);
		if (!temp1)
			return (free(temp), -1);
		free(*str);
		*str = temp1;
		free(temp);
		*in_quotes = check - *in_quotes;
		return (1);
	}
	return (0);
}

bool	remove_quotes(char **str)
{
	int	in_quotes;
	int	i;
	int	res;

	i = 0;
	in_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			res = remove_quote(str, i, &in_quotes);
			if (res == -1)
				return (false);
			else if (res == 0)
				i++;
			continue ;
		}
		i++;
	}
	return (true);
}
