/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:17:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 13:40:39 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_n_flag(const char *s)
{
	if (!s || s[0] != '-' || s[1] != 'n')
		return (false);
	s += 2;
	while (*s == 'n')
		s++;
	return (*s == '\0');
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	bool	has_newline;

	i = 1;
	has_newline = true;
	while (cmd->args[i] && is_valid_n_flag(cmd->args[i]))
	{
		has_newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		if (printf("%s", cmd->args[i++]) == -1)
			return (handle_error("echo: write error"));
		if (cmd->args[i])
			if (printf(" ") == -1)
				return (handle_error("echo: write error"));
	}
	if (has_newline)
		if (printf("\n") == -1)
			return (handle_error("echo: write error"));
	return (0);
}
