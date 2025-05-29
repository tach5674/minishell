/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 13:29:54 by ggevorgi         ###   ########.fr       */
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
		shell->commands = readline("\033[1;32mminishell$ \033[0m");
		if (!shell->commands)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*shell->commands)
		{
			add_history(shell->commands);
			execute_commands(shell);
		}
		free(shell->commands);
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}
