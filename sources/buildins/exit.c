/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:29:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/20 22:02:10 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd)
{
	if (cmd->args[2])
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		ft_putstr_fd("exit\n", 1);
		if (cmd->args[1])
			exit(ft_atoi(cmd->args[1]));
		exit(0);
	}
}
