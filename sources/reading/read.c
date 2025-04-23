/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:49:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/23 15:03:01 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_promt(void)
{
	char	*line;

	line = readline("\033[1;32mminishell$ \033[0m");
	if (line && *line)
		add_history (line);
	return (line);
}
