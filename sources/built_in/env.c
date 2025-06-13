/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:49:05 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 14:54:00 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_ht *env)
{
	if (cmd->args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (ht_print(env) == -1)
		return (handle_error("env: write error"));
	return (0);
}
