/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:06:48 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/02 13:52:15 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int add_if_valid(t_ht *env, char *str, char *name, int i)
{
    char *key;
	char *value;

	if (str[i] == '=')
	{
		key = ft_substr(str, 0, i);
		if (!key)
			return (handle_error(name));
		value = ft_substr(str, i + 1, ft_strlen(str));
		if (!value)
		{
			free(key);
			return (handle_error(name));
		}
		if (ht_add(env, key, value) == false)
		{
			free(key);
			free(value);
			return (handle_error(name));
		}
		free(key);
		free(value);
	}
	return (0);
}

static int	check_if_valid(char *str)
{
	int i;
	
    if (ft_isdigit(*str) || *str == '=')
        return (0);
    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
		i++;
    }
	return (i);
}

int ft_export(t_cmd *cmd, t_ht *env)
{
	int	i;
	
    if (!cmd->args[1])
	{
		if (ht_print(env) == -1)
			return (handle_error("export: write error: "));
		return (0);
	}
	i = check_if_valid(cmd->args[1]);
	if (i == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	return (add_if_valid(env, cmd->args[1], cmd->name, i));
}