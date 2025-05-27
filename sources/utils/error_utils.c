/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:53:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/27 18:50:53 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(const char *err, const char *msg)
{
	if (msg)
		printf("\033[1;31m%s\033[0m%s", err, msg);
	else
		printf("\033[1;31m%s\033[0m", err);
	return (4);
}

void	throw_err(int err_type)
{
	if (err_type == MALLOC_ERROR)
	{
		print_error("Error: Memory allocation failed.\n", NULL);
		exit(MALLOC_ERROR);
	}
	else if (err_type == INVALID_ARGUMENT_ERROR)
	{
		print_error("Error: This program does not"
			" accept any arguments.\n", NULL);
		exit(INVALID_ARGUMENT_ERROR);
	}
	else
	{
		print_error("Unexpected program error.\n", NULL);
		exit(EXIT_FAILURE);
	}
	rl_clear_history();
}

void	syntax_error(const char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
}
