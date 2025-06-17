/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:49:56 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/17 12:52:51 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_export(t_cmd *cmd, t_export_state *state)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->args[state->j], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ht_print_export_default(t_ht *ht)
{
	char	**htcpy;
	size_t	i;

	if (!ht)
		return (1);
	htcpy = ht_to_envp(ht, true);
	if (!htcpy)
		return (1);
	sorter(htcpy, ht->count);
	i = 0;
	while (i < ht->count)
	{
		if (print_export_line(htcpy[i]) == -1)
			return (-1);
		i++;
	}
	free_list(htcpy, ht->count);
	return (0);
}

int	add_no_value(t_ht *env, char **args, t_export_state *state)
{
	char	*key;

	key = ft_substr(args[state->j], 0, state->i);
	if (!key)
		return (handle_error(args[0]));
	if (ht_get(env, key))
		return (free(key), 0);
	if (ht_add_no_value(env, key) == false)
	{
		free(key);
		return (handle_error(args[0]));
	}
	free(key);
	return (0);
}
