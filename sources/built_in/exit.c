/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:29:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 18:04:26 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	clean_return_exit_code(t_shell *shell, int exit_code)
{
	free_shell(shell);
	return (exit_code);
}

static bool	is_numerical(const char *str)
{
	if (*str == '-')
	{
		str++;
		if (ft_strlen(str) > 19 || ft_strcmp(str, "9223372036854775808") > 0)
			return (false);
	}
	else if (*str == '+' || ft_isdigit(*str))
	{
		if (*str == '+')
			str++;
		if (ft_strlen(str) > 19 || ft_strcmp(str, "9223372036854775807") > 0)
			return (false);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ft_exit(t_cmd *cmd, t_shell *shell)
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
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(clean_return_exit_code(shell, 2));
	}
	exit(clean_return_exit_code(shell, 0));
}
