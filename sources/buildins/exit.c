/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:29:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 18:57:08 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_return_exit_code(t_shell *shell, int exit_code)
{
	free_shell(shell);
	return (exit_code);
}

bool	is_numerical(const char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int		ft_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->in_subshell == false)
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
			exit(clean_return_exit_code(shell, ft_atoi(cmd->args[1])));
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[1], 2);		
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		exit(clean_return_exit_code(shell, ft_atoi(cmd->args[1])));
	}
	exit(clean_return_exit_code(shell, 0));
}
