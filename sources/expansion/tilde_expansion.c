/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:25 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/10 14:36:31 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	recreate_string(char **str, t_ht *env, int i, char *path)
{
	char	*temp;
	int		len;
	
	len = 0;
	temp = ht_get(env, path);
	if (temp)
	{
		len = ft_strlen(temp);
		(*str)[i] = '\0';
		temp = ft_strjoin(*str, temp);
		if (!temp)
			return (-1);
		free(*str);
		*str = temp;
	}
	return (len - 1);
}

static int	recreate_string_slash(char **str, t_ht *env, int i)
{
	char	*temp;
	char	*temp1;
	int		len;

	len = 0;
	temp = ht_get(env, "HOME");
	if (temp)
	{
		len = ft_strlen(temp);
		(*str)[i] = '\0';
		temp = ft_strjoin(*str, temp);
		if (!temp)
			return (-1);
		temp1 = ft_strjoin(temp, *str + i + 1);
		if (!temp1)
			return (free(temp), -1);
		free(temp);
		free(*str);
		*str = temp1;
	}
	return (len - 1);
}

static int	expand_tilde_helper(char **str, int i, t_ht *env)
{
	if (i == 0 || check_if_valid(*str))
	{
		if ((*str)[i + 1] == '+' && !((*str)[i + 2]))
			return (recreate_string(str, env, i, "PWD"));
		else if ((*str)[i + 1] == '-' && !((*str)[i + 2]))
			return (recreate_string(str, env, i, "OLDPWD"));
		else if ((*str)[i + 1] == '/')
			return (recreate_string_slash(str, env, i));
		else if (!((*str)[i + 1]))
			return (recreate_string(str, env, i, "HOME"));
	}
	return (0);
}

bool	expand_tilde(char **str, t_ht *env)
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
		else if ((*str)[i] == '~' && in_quotes == 0)
		{
			len = expand_tilde_helper(str, i, env);
			if (len == -1)
				return (false);
			i += len;
		}
		i++;
	}
	return (true);
}