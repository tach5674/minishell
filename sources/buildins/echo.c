/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:17:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/20 21:52:00 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_n_flag(char *s)
{
	if (*s == '-')
		++s;
	while (*s && *s == 'n')
		++s;
	if (*s)
		return (false);
	return (true);
}

void	ft_echo(t_cmd *cmd)
{
	bool	is_nl;
	int		first_arg;

	first_arg = 1;
	is_nl = has_n_flag(cmd->args[first_arg]);
	if (is_nl)
		++first_arg;
	while (cmd->args[first_arg])
		printf("%s", cmd->args[first_arg++]);
	if (is_nl)
		write(1, "\n", 1);
}
