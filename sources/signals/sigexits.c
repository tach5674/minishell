/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigexits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:41 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/30 16:47:50 by ggevorgi         ###   ########.fr       */
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

static void	exec_signal_handler(int sig)
{
	signal_status = sig;
}

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

// void	sig_handler_hdoc(int sig)
// {
// 	(void)sig;
// 	signal_status = sig;
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }

// void	setup_heredoc_signals(void)
// {
//     signal(SIGINT, sig_handler_hdoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	setup_signals_parent_exec(void)
{
    signal(SIGINT, exec_signal_handler);
    signal(SIGQUIT, exec_signal_handler);
}
