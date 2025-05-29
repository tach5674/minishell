/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 17:00:05 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;
	int		exit_code;
	
	shell = safe_malloc(sizeof(t_shell));
	shell_init(shell, envp);
	if (argc > 1 && argv)
		throw_err(INVALID_ARGUMENT_ERROR);
	setup_signals();
	while (1)
	{
		shell->commands = readline("\033[1;32mminishell$ \033[0m");
		if (!shell->commands)
			break ;
		if (*shell->commands)
		{
			add_history(shell->commands);
			execute_commands(shell);
			if (shell->exit_code >= 0)
				break;
		}
	}
	ft_putstr_fd("exit\n", 1);
	exit_code = shell->exit_code;
	free_shell(shell);
	return (exit_code);
}
