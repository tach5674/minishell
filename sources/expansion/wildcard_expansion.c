/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 14:55:59 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_flags(char *str, bool *only_dir, bool *show_hidden)
{
	int	len;

	*only_dir = false;
	*show_hidden = false;
	if (*str == '.')
		*show_hidden = true;
	len = ft_strlen(str);
	while (len--)
	{
		if (str[len] == '/')
		{
			*only_dir = true;
			break ;
		}
		else if (str[len] == '\'' || str[len] == '"')
			continue ;
		else
			break ;
	}
}

bool	expand_wildcards(t_cmd *cmd, size_t *i)
{
	int		count;
	char	**match_list;
	bool	show_hidden;
	bool	only_dir;

	if (!contains_wildcard(cmd->args[*i]))
		return (true);
	count = 0;
	set_flags(cmd->args[*i], &only_dir, &show_hidden);
	match_list = wildcard_expand((cmd->args[*i]), &count, show_hidden,
			only_dir);
	if (!match_list)
		return (false);
	if (append_to_arguments(cmd, match_list, *i, count) == false)
		return (false);
	*i += count - 1;
	return (true);
}

bool	expand_wildcards_redir(char **str)
{
	int		count;
	char	**match_list;
	bool	show_hidden;
	bool	only_dir;

	if (!contains_wildcard(*str))
		return (true);
	count = 0;
	set_flags(*str, &only_dir, &show_hidden);
	match_list = wildcard_expand(*str, &count, show_hidden, only_dir);
	if (!match_list)
		return (false);
	if (count > 1)
	{
		ft_putstr_fd("minishell: *: ambigous redirect\n", 2);
		free_list(match_list, count);
		return (false);
	}
	free(*str);
	*str = match_list[0];
	free(match_list);
	return (true);
}
