/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:42:32 by mzohraby          #+#    #+#             */
/*   Updated: 2025/05/30 18:50:50 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_cmd *cmd, t_ht *env)
{
    if (cmd->args[1])
    {
        if (chdir(cmd->args[1]) == -1)
            return (handle_error(cmd->name));
        ht_add(env, "OLDPWD", ht_get(env, "PWD"));        
        ht_add(env, "PWD", cmd->args[1]);
        return (0);
    }
    return (EXIT_FAILURE);
}