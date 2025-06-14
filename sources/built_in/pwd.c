/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:58:23 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 16:41:21 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_ht *env)
{
	char	cwd[PATH_MAX];

	(void)env;
	(void)cmd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (printf("%s\n", cwd) == -1)
			return (handle_error("pwd: write error"));
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}
