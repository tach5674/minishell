/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:54:18 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 14:21:08 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_ht *env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], "_"))
			ht_unset(env, cmd->args[i]);
		i++;
	}
	return (0);
}
