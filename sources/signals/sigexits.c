/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigexits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:41 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/23 15:20:41 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);     // Ctrl-C
	signal(SIGQUIT, SIG_IGN);           // Ctrl-
}
