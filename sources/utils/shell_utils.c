/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:42:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/13 17:01:48 by ggevorgi         ###   ########.fr       */
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
	shell->env = ht_init(envp);
	shell->last_status_code = 0;
	shell->shell_name = "minishell";
}
