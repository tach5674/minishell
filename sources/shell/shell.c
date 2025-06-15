/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:42:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/15 15:17:27 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	ht_free(shell->env);
	free_ast(shell->ast);
	cleanup_heredocs(shell);
	free(shell->last_status_code);
	free(shell);
	rl_clear_history();
}

void	shell_init(t_shell *shell, char **envp)
{
	shell->last_status_code = ft_strdup("0");
	if (!shell->last_status_code)
		throw_err(MALLOC_ERROR);
	tcgetattr(STDIN_FILENO, &shell->original_termios);
	shell->shell_envp = envp;
	shell->env = ht_init(envp);
	shell->shell_name = "minishell";
	shell->commands = NULL;
	shell->heredocs = NULL;
	shell->heredoc_need_to_expand = true;
	shell->ast = NULL;
}
