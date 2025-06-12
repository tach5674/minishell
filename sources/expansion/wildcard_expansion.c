/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:17 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 19:06:26 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char	**wildcard_expand(const char *pattern, int *count, bool show_hidden,
// 		bool only_dir)
// {
// 	DIR				*dir;
// 	struct dirent	*ent;
// 	char			**match_list;
// 	int				capacity;
// 	struct stat		statbuf;

// 	capacity = 0;
// 	dir = opendir(".");
// 	if (!dir)
// 		return (NULL);
// 	while (1)
// 	{
// 		ent = readdir(dir);
// 		if (ent == NULL)
// 			break ;
// 		if (*(ent->d_name) == '.' && !show_hidden)
// 			continue ;
// 		if (stat(ent->d_name, &statbuf) != 0)
// 			return (NULL);
// 		if (only_dir && !S_ISDIR(statbuf.st_mode))
// 			continue ;
// 		if (matches(pattern, ent->d_name))
// 		{
// 			if ((*count) == capacity)
// 			{
// 				if (resize_list(&match_list, &capacity) == false)
// 					return (NULL);
// 			}
// 			if (only_dir)
// 				match_list[(*count)] = ft_strjoin(ent->d_name, "/");
// 			else
// 				match_list[(*count)] = strdup(ent->d_name);
// 			if (!match_list[(*count)])
// 				return (free_list(match_list, (*count)), NULL);
// 			(*count)++;
// 		}
// 	}
// 	closedir(dir);
// 	if ((*count) == 0)
// 	{
// 		match_list = malloc(sizeof(char *));
// 		if (!match_list)
// 			return (NULL);
// 		match_list[0] = strdup(pattern);
// 		if (!match_list[0])
// 			return (free(match_list), NULL);
// 		(*count) = 1;
// 	}
// 	else
// 		sorter(match_list, *count);
// 	return (match_list);
// }

void	check_if_only_dir(char *str, bool *only_dir, bool *show_hidden)
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
	check_if_only_dir(cmd->args[*i], &only_dir, &show_hidden);
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
	check_if_only_dir(*str, &only_dir, &show_hidden);
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
