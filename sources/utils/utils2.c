/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:08:00 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/14 20:58:00 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t bytes)
{
	void	*malloced;

	malloced = malloc(bytes);
	if (!malloced)
	{
		throw_err(MALLOC_ERROR);
		return (NULL);
	}
	return (malloced);
}

void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	cleanup_heredocs(t_shell *shell)
{
	t_heredoc	*tmp;

	while (shell->heredocs)
	{
		tmp = shell->heredocs;
		shell->heredocs = shell->heredocs->next;
		unlink(tmp->filename);
		free(tmp->filename);
		free(tmp);
	}
	shell->heredocs = NULL;
}

void	print_quit(void)
{
	write(1, "Quit (core dumped)\n", 19);
	g_signal_status = 0;
}

void	check_interactive_sigint(t_shell *shell)
{
	if (g_signal_status == SIGINT)
	{
		if (shell->last_status_code)
			free(shell->last_status_code);
		shell->last_status_code = ft_itoa(130);
		if (!shell->last_status_code)
			perror("minishell");
		g_signal_status = 0;
	}
}