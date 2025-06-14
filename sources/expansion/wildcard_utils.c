/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:06:21 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/14 15:47:19 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	append_to_arguments(t_cmd *cmd, char **match_list, size_t i, int count)
{
	char	**new_args;
	size_t	j;
	size_t	old_size;
	int		k;

	old_size = 0;
	while (cmd->args[old_size])
		old_size++;
	new_args = malloc((old_size + count + 1) * sizeof(char *));
	if (!new_args)
		return (perror("minishell"), false);
	j = -1;
	while (++j < i)
		new_args[j] = cmd->args[j];
	k = 0;
	while (k < count)
		new_args[j++] = match_list[k++];
	free(cmd->args[i]);
	i++;
	while (i < old_size)
		new_args[j++] = cmd->args[i++];
	new_args[j] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (true);
}

bool	contains_wildcard(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (quote == *str)
				quote = 0;
			else
				quote = *str;
		}
		else if (*str == '*' && quote == 0)
			return (true);
		str++;
	}
	return (false);
}

void	free_list(char **arr, int n)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

bool	resize_list(char ***list, int *capacity)
{
	char	**new_list;
	int		count;

	count = *capacity;
	if (*capacity == 0)
	{
		*capacity = 16;
		*list = malloc(*capacity * sizeof(char *));
		if (!(*list))
			return (false);
	}
	else
		*capacity *= 2;
	new_list = malloc(*capacity * sizeof(char *));
	if (!new_list)
		return (free_list(*list, count), false);
	while (count--)
		new_list[count] = (*list)[count];
	free(*list);
	*list = new_list;
	return (true);
}
