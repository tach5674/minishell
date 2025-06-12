/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:08:00 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 18:15:28 by mzohraby         ###   ########.fr       */
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

void	swap(char **match_list, int i, int j)
{
	char	*temp;

	temp = match_list[i];
	match_list[i] = match_list[j];
	match_list[j] = temp;
}

void	sorter(char **match_list, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(match_list[j], match_list[j + 1]) > 0)
				swap(match_list, j, j + 1);
			j++;
		}
		i++;
	}
}
