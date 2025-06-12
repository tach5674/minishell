/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:08:43 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 17:36:53 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_ht *env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
		ht_unset(env, cmd->args[i++]);
	return (0);
}
