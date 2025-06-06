/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigexits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:41 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/06 16:34:01 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

int	signal_status;

static void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// static void	exec_signal_handler(int sig)
// {
// 	signal_status = sig;
// }

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)	
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_parent_exec(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_parent_heredoc(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
