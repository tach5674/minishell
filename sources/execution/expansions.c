/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:38 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/06 14:39:28 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	recreate_string(char **str, t_shell *shell, int i, char *path)
{
	char	*temp;
	
	temp = ht_get(shell->env, path);
	if (temp)
	{
		(*str)[i] = '\0';
		temp = ft_strjoin(*str, temp);
		if (!temp)
			return (false);
		free(*str);
		*str = temp;
	}
	return (true);
}

bool	recreate_string_slash(char **str, t_shell *shell, int i)
{
	char	*temp;
	char	*temp1;
	
	temp = ht_get(shell->env, "HOME");
	if (temp)
	{
		(*str)[i] = '\0';
		temp = ft_strjoin(*str, temp);
		if (!temp)
			return (false);
		temp1 = ft_strjoin(temp, *str + i + 1);
		if (!temp1)
			return (false);
		free(temp);
		free(*str);
		*str = temp1;
	}
	return (true);
}

bool	expand_tilde(char **str, int i, t_shell *shell)
{
	if (i == 0 || check_if_valid(*str))
	{
		if ((*str)[i + 1] == '+' && !((*str)[i + 2]))
			return (recreate_string(str, shell, i, "PWD"));
		else if ((*str)[i + 1] == '-' && !((*str)[i + 2]))
			return (recreate_string(str, shell, i, "OLDPWD"));
		else if ((*str)[i + 1] == '/')
			return (recreate_string_slash(str, shell, i));
		else if (!((*str)[i + 1]))
			return (recreate_string(str, shell, i, "HOME"));
	}
	return (true);
}

bool	check_if_quotes(char *str, int *in_quotes, int i)
{
	if (str[i] == '\'')
	{
		if (*in_quotes == 0)
			*in_quotes = 1;
		else if (*in_quotes == 1)
			*in_quotes = 0;
		return (true);
	}
	else if (str[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = 2;
		else if (*in_quotes == 2)
			*in_quotes = 0;
		return (true);
	}
	return (false);
}

bool	expand(char **str, t_shell *shell)
{
	int	in_quotes;
	int	i;
	
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
			if (expand_tilde(str, i, shell) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

// bool	remove_quotes(char **str)
// {
// 	int	in_quotes;
// 	int	i;
	
// 	i = 0;
// 	in_quotes = 0;
// 	while ((*str)[i])
// 	{
// 		if (check_if_quotes(*str, &in_quotes, i) == true)
// 		{
// 			if (in_quotes)
			
// 		}
// 	}
// 	return (true);
// }

bool    apply_expansions(char **args, t_shell *shell)
{
    int	i;

	i = 0;
    while (args[i])
	{
		if (expand(&args[i], shell) == false)
		{
			perror("minishell");
			return (false);
		}
		// if (remove_quotes(&args[i]) == false)
		// {
		// 	perror("minishell");
		// 	return (false);
		// }
		i++;
	}
	return (true);
}