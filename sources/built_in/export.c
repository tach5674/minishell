/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:06:48 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 14:50:56 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_to_val(t_ht *env, char *key, char *value)
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

static int	add_if_valid(t_ht *env, char **args, t_export_state *state,
		int check)
{
	char	*key;
	char	*value;

	key = ft_substr(args[state->j], 0, state->i);
	if (!key)
		return (handle_error(args[0]));
	value = ft_substr(args[state->j], state->i + 1 + check,
			ft_strlen(args[state->j]));
	if (!value)
		return (free(key), handle_error(args[0]));
	if (check && ht_get(env, key))
	{
		value = append_to_val(env, key, value);
		if (!value)
			return (handle_error(args[0]));
	}
	if (ht_add(env, key, value) == false)
	{
		free(key);
		free(value);
		return (handle_error(args[0]));
	}
	free(key);
	free(value);
	return (0);
}

static int	check_if_valid(char *str)
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

static int	ft_export_helper(t_export_state *state, t_cmd *cmd, t_ht *env)
{
	if (cmd->args[state->j][state->i] == '=' && cmd->args[state->j][state->i
		- 1] == '+')
	{
		state->i--;
		state->return_code = add_if_valid(env, cmd->args, state, 1);
		if (state->return_code != 0)
			return (state->return_code);
	}
	else if (cmd->args[state->j][state->i] == '=')
	{
		state->return_code = add_if_valid(env, cmd->args, state, 0);
		if (state->return_code != 0)
			return (state->return_code);
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_ht *env)
{
	t_export_state	state;

	state.exit_code = 0;
	if (!cmd->args[1])
	{
		if (ht_print_export_default(env) == -1)
			return (handle_error("export: write error: "));
		return (0);
	}
	state.j = 0;
	while (cmd->args[++state.j])
	{
		state.i = check_if_valid(cmd->args[state.j]);
		if (state.i == 0)
		{
			print_error_export(cmd, &state);
			state.exit_code = EXIT_FAILURE;
			continue ;
		}
		ft_export_helper(&state, cmd, env);
		if (state.return_code)
			return (state.return_code);
	}
	return (state.exit_code);
}
