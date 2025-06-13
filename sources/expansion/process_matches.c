/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_matches.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:05:20 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 19:16:04 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_add_entry(t_expand_state *state, struct dirent *ent)
{
	struct stat	statbuf;

	if (ent->d_name[0] == '.' && !state->show_hidden)
		return (false);
	if (stat(ent->d_name, &statbuf) != 0)
		return (false);
	if (state->only_dir && !S_ISDIR(statbuf.st_mode))
		return (false);
	return (matches(state->pattern, ent->d_name));
}

static bool	add_matching_entry(t_expand_state *state, struct dirent *ent)
{
	char	*new_entry;

	if (*(state->count) == *(state->capacity))
	{
		if (!resize_list(state->match_list, state->capacity))
			return (false);
	}
	if (state->only_dir)
		new_entry = ft_strjoin(ent->d_name, "/");
	else
		new_entry = ft_strdup(ent->d_name);
	if (!new_entry)
		return (false);
	(*(state->match_list))[(*state->count)++] = new_entry;
	return (true);
}

static char	**create_default_match(const char *pattern, int *count)
{
	char	**match_list;

	match_list = malloc(sizeof(char *));
	if (!match_list)
		return (NULL);
	match_list[0] = ft_strdup(pattern);
	if (!match_list[0])
	{
		free(match_list);
		return (NULL);
	}
	*count = 1;
	return (match_list);
}

static char	**process_matches(t_expand_state *state)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (should_add_entry(state, ent) && !add_matching_entry(state, ent))
		{
			closedir(dir);
			free_list(*(state->match_list), *state->count);
			return (NULL);
		}
		ent = readdir(dir);
	}
	closedir(dir);
	if (*state->count == 0)
		return (create_default_match(state->pattern, state->count));
	sorter(*(state->match_list), *state->count);
	return (*(state->match_list));
}

char	**wildcard_expand(const char *pattern, int *count, bool show_hidden,
		bool only_dir)
{
	t_expand_state	state;
	char			**match_list;
	int				capacity;

	match_list = NULL;
	capacity = 0;
	*count = 0;
	state.match_list = &match_list;
	state.pattern = pattern;
	state.show_hidden = show_hidden;
	state.only_dir = only_dir;
	state.capacity = &capacity;
	state.count = count;
	return (process_matches(&state));
}
