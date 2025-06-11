/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/11 15:38:10 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = safe_malloc(sizeof(t_shell));
	shell_init(shell, envp);
	if (argc > 1 && argv)
		throw_err(INVALID_ARGUMENT_ERROR);
	setup_signals();
	while (1)
	{
		errno = 0;
		if (signal_status == SIGINT)
        	write(1, "\n", 1);
    	else if (signal_status == SIGQUIT)
       		write(1, "Quit (core dumped)\n", 19);
    	signal_status = 0;
		shell->commands = readline("\033[1;32mminishell$ \033[0m");
		if (!shell->commands)
			break ;
		if (*shell->commands)
			execute_commands(shell);
	}
	free_shell(shell);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
