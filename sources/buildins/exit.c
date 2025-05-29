/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:29:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 01:23:50 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_shell *shell_data, int exit_code)
{
	free_shell(shell_data);
	rl_clear_history();
	exit(exit_code);
}

bool	is_numerical(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int		ft_exit(t_cmd *cmd, t_shell *shell_data)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd->args[1])
	{
		if (is_numerical(cmd->args[1]))
		{
			if (cmd->args[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				return (EXIT_FAILURE);
			}
			clean_exit(shell_data, ft_atoi(cmd->args[1]));
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[1], 2);		
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		clean_exit(shell_data, ft_atoi(cmd->args[1]));
	}
	free_shell(shell_data);
	rl_clear_history();
	exit(0);
}
