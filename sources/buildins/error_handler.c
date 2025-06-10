/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:33:47 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/10 14:34:00 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_error(char *name)
{
	char    *msg;
    
    msg = ft_strjoin("minishell: ", name);
    if (!msg)
    {
        perror("minishell");
        return (EXIT_FAILURE);
    }
    perror(msg);
    free(msg);
    return (EXIT_FAILURE);
}