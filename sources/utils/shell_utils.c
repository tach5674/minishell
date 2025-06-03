/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:42:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/03 12:31:37 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	ht_free(shell->env);
	free_ast(shell->ast);
	free(shell);
	rl_clear_history();
}

void	shell_init(t_shell *shell, char **envp)
{
	tcgetattr(STDIN_FILENO, &shell->original_termios);
	shell->shell_envp = envp;
	shell->env = ht_init(envp);
	shell->last_status_code = 0;
	shell->shell_name = "minishell";
	shell->commands = NULL;
	shell->ast = NULL;
}
