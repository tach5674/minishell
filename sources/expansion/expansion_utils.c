/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:19 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/17 16:58:15 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_expansions(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambigous redirect\n", 2);
}

bool	check_if_quotes(char *str, char *in_quotes, int i)
{
	if (str[i] == '\'' || str[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = str[i];
		else if (*in_quotes == str[i])
			*in_quotes = 0;
		return (true);
	}
	return (false);
}

int	expand_empty(t_cmd *cmd, int j, t_ht *env)
{
	int	i;

	if (ft_isdigit((cmd->args[j])[1]))
	{
		if (ft_strlen((cmd->args[j])) == 2)
			return (append_to_arguments(cmd, NULL, j, 0));
		return (2);
	}
	i = 1;
	while ((cmd->args[j])[i])
	{
		if (!ft_isalnum((cmd->args[j])[i]) && (cmd->args[j])[i] != '_')
			break ;
		i++;
	}
	if ((cmd->args[j])[i] == '\0')
	{
		if (ht_get(env, cmd->args[j] + 1) == false)
			return (append_to_arguments(cmd, NULL, j, 0));
	}
	return (2);
}
