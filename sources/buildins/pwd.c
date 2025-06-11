/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:58:23 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/11 17:26:04 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_ht *env)
{
	char	cwd[PATH_MAX];

	(void)env;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
	{
		if (printf("%s\n", cwd) == -1)
			return (handle_error("pwd: write error"));
	}
	else
		return (handle_error(cmd->args[0]));
	return (0);
}
