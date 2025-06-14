/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:19 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/14 15:37:48 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_expansions(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambigous redirect\n", 2);
}

bool	check_if_quotes(char *str, char *in_quotes, int i)
{
	if (str[i] == '\'' || str[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = str[i];
		else if (*in_quotes == str[i])
			*in_quotes = 0;
		return (true);
	}
	return (false);
}
