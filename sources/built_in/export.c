/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:06:48 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/12 13:40:27 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_to_val(t_ht *env, char *key, char *value)
{
	char	*temp;

	temp = ft_strjoin(ht_get(env, key), value);
	free(value);
	if (!temp)
	{
		free(key);
		return (NULL);
	}
	return (temp);
}

static int	add_if_valid(t_ht *env, char *str, char *name, int i, int check)
{
	char	*key;
	char	*value;

	key = ft_substr(str, 0, i);
	if (!key)
		return (handle_error(name));
	value = ft_substr(str, i + 1 + check, ft_strlen(str));
	if (!value)
		return (free(key), handle_error(name));
	if (check && ht_get(env, key))
	{
		value = append_to_val(env, key, value);
		if (!value)
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
	return (0);
}

int	check_if_valid(char *str)
{
	int	i;

	if (ft_isdigit(*str) || *str == '=')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (i + 1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

int	ft_export(t_cmd *cmd, t_ht *env)
{
	int i;

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
	if (cmd->args[1][i] == '=' && cmd->args[1][i - 1] == '+')
		return (add_if_valid(env, cmd->args[1], cmd->args[0], i - 1, 1));
	else if (cmd->args[1][i] == '=')
		return (add_if_valid(env, cmd->args[1], cmd->args[0], i, 0));
	return (0);
}