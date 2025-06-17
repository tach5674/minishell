/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:21:58 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/17 16:52:37 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_quoted_string(const char *str)
{
	int		word_count;
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&str);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

bool	split_arguments(t_cmd *cmd, int j)
{
	char	**res;
	int		count;

	count = 0;
	res = split_quoted_string(cmd->args[j]);
	if (!res)
		return (perror("minishell"), false);
	while (res[count])
		count++;
	if (count > 1)
	{
		if (append_to_arguments(cmd, res, j, count) == false)
			return ((free(res), false));
		free(res);
		return (true);
	}
	free_list(res, count);
	return (true);
}

bool	split_arguments_redir(char *str)
{
	char	**res;
	int		count;

	count = 0;
	res = split_quoted_string(str);
	if (!res)
		return (perror("shell"), false);
	while (res[count])
		count++;
	if (count > 1)
	{
		ft_putstr_fd("minishell: *: ambigous redirect\n", 2);
		free_list(res, count);
		return (false);
	}
	free_list(res, count);
	return (true);
}
