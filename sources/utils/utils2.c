/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:08:00 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/14 10:53:18 by ggevorgi         ###   ########.fr       */
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
