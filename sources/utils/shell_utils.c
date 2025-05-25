/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:42:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/25 13:22:23 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	ht_free(shell->env);
	free(shell);
}

void	shell_init(t_shell *shell, char **envp)
{
	shell->shell_envp = envp;
	shell->env = ht_init(envp);
	shell->last_status_code = 0;
	shell->shell_name = "minishell";
}
