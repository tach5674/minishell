/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:33:47 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/29 01:24:52 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_error(char *name)
{
	char    *msg;
    
    msg = ft_strjoin("minishell: ", name);
    perror(msg);
    free(msg);
    return (EXIT_FAILURE);
}