/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 16:03:57 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset(t_shell *shell)
{
	if (g_signal_status == SIGINT)
		write(1, "\n", 1);
	else if (g_signal_status == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	g_signal_status = 0;
	free_ast(shell->ast);
	cleanup_heredocs(shell);
	shell->ast = NULL;
	shell->is_heredoc_need_to_expand = false;
}

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
		reset(shell);
		shell->commands = readline(
				"\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!shell->commands)
			break ;
		if (*shell->commands)
			execute_commands(shell);
		else
			free(shell->commands);
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_termios);
	}
	free_shell(shell);
	return (ft_putstr_fd("exit\n", 1), 0);
}
