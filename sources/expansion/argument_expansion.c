/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:09 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/13 12:53:07 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	place_non_empty(char **str, int i, int start, char *temp)
{
	int		len;
	char	*temp1;

	len = ft_strlen(temp);
	(*str)[start] = '\0';
	temp = ft_strjoin(*str, temp);
	if (!temp)
		return (-1);
	temp1 = ft_strjoin(temp, *str + i);
	if (!temp1)
		return (free(temp), -1);
	free(temp);
	free(*str);
	*str = temp1;
	return (len);
}

static int	place_argument(char **str, int i, int start, t_ht *env)
{
	char	*temp;
	char	*temp1;

	temp1 = ft_substr(*str, start + 1, i - start - 1);
	if (!temp1)
		return (false);
	temp = ht_get(env, temp1);
	free(temp1);
	if (!temp)
	{
		(*str)[start] = '\0';
		temp = ft_strjoin(*str, *str + i);
		if (!temp)
			return (-1);
		free(*str);
		*str = temp;
		return (0);
	}
	else
		return (place_non_empty(str, i, start, temp));
}

static int	expand_argument(char **str, int i, t_ht *env)
{
	int	start;

	start = i;
	i++;
	if (ft_isdigit((*str)[i]))
		return (place_argument(str, i + 1, start, env));
	if (!ft_isalnum((*str)[i]) && (*str)[i] != '_')
		return (1);
	while ((*str)[i])
	{
		if (!ft_isalnum((*str)[i]) && (*str)[i] != '_')
			break ;
		i++;
	}
	return (place_argument(str, i, start, env));
}

bool	expand_arguments(char **str, t_shell *shell)
{
	char	in_quotes;
	int		i;
	int		len;

	i = 0;
	in_quotes = 0;
	while ((*str)[i])
	{
		check_if_quotes(*str, &in_quotes, i);
		if ((*str)[i] == '$' && in_quotes != '\'')
		{
			if ((*str)[i + 1] == '?')
				len = place_non_empty(str, i + 2, i, shell->last_status_code);
			else if ((*str)[i + 1] == '0')
				len = place_non_empty(str, i + 2, i, shell->shell_name);
			else
				len = expand_argument(str, i, shell->env);
			if (len == -1)
				return (false);
			i += len - 1;
		}
		i++;
	}
	return (true);
}
