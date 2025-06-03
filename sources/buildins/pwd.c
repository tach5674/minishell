/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:58:23 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/02 18:41:11 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_ht *env)
{
	char	cwd[PATH_MAX];

	(void)env;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		return (handle_error(cmd->name));
	return (0);
}
