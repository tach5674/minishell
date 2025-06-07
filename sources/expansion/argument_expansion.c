/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:09 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/07 12:55:20 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		place_non_empty(char **str, int i, int start, char *temp)
{
	int	len;
	char *temp1;
	
	len = ft_strlen(temp);
	(*str)[start] = '\0';
	temp = ft_strjoin(*str, temp);
	if (!temp)
		return (-1);
	temp1 = ft_strjoin(temp, *str + i);
	if (!temp1)
		return (-1);
	free(temp);
	free(*str);
	*str = temp1;
	return (len - 1);
}

int		place_argument(char **str, int i, int start, t_ht *env)
{
	char	*temp;
	char	*temp1;

	temp1 = ft_substr(*str, start + 1, i - 1);
	if (!temp1)
		return (false);
	temp = ht_get(env, temp1);
	free(temp1);
	if (!temp)
	{
		(*str)[start] = '\0';
		temp = ft_strjoin(*str, *str + i);
		free(*str);
		*str = temp;
		return (-1);
	}
	else
		return (place_non_empty(str, i, start, temp));
}

int	expand_argument(char **str, int i, t_ht *env)
{
	int		start;

	start = i;
	i++;
	while ((*str)[i])
	{
		if (!ft_isalnum((*str)[i]) && (*str)[i] != '_')
			break ;
		i++;
	}
	return (place_argument(str, i, start, env));
}

bool	expand_arguments(char **str, t_ht *env)
{
	int	in_quotes;
	int	i;
	int	len;
	
	i = 0;
	in_quotes = 0;
	while ((*str)[i])
	{
		if (check_if_quotes(*str, &in_quotes, i))
		{
			i++;
			continue;
		}
		else if ((*str)[i] == '$' && in_quotes != 1)
		{
			len = expand_argument(str, i, env);
			if (len == false)
				return (false);
			i += len;
		}
		i++;
	}
	return (true);
}