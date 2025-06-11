/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/11 13:10:52 by ggevorgi         ###   ########.fr       */
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
		if (signal_status == SIGINT)
        	write(1, "\n", 1);
    	else if (signal_status == SIGQUIT)
       		write(1, "Quit (core dumped)\n", 19);
    	signal_status = 0;
		shell->commands = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!shell->commands)
			break ;
		if (*shell->commands)
			execute_commands(shell);
	}
	free_shell(shell);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
