/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:17 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/11 16:35:05 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "minishell.h"

// Helper function to match pattern against text (supports '*' wildcards)
static int matches(const char *p, const char *s) {
    // const char *s = text;     // Current position in text
    // const char *p = pattern;  // Current position in pattern
    const char	*star = NULL;  // Last '*' position in pattern
    const char	*ss = s;       // Position in text after last star
	char		quote;

	quote = 0;
    while (*s) {
		if (*p == '\'' || *p == '"')
		{
			if (quote == *p)
				quote = 0;
			else	
				quote = *p;
			p++;
		}
        else if (*p == *s) {  // Characters match
            p++;
            s++;
        } else if (!quote && *p == '*') {  // Wildcard found
            star = p;    // Remember star position
            ss = s;      // Remember current text position
            p++;         // Move to next character in pattern
        } else if (star) {  // Mismatch but previous star exists
            p = star + 1;   // Reset pattern to after star
            s = ++ss;       // Advance text and retry
        } else {
            return 0;  // No match and no star to backtrack
        }
    }
    // Skip any remaining '*' in pattern
    while (*p == '*' || *p == '\'' || *p == '"')
		p++;
	while (*p == '/' || *p == '\'' || *p == '"')
		p++;
    // Match if pattern is exhausted
    return (*p == '\0');
}

// Comparison function for qsort
// static int cmpstring(const void *a, const void *b) 
// {
//     return strcmp(*(const char **)a, *(const char **)b);
// }

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

bool resize_list(char ***list, int *capacity)
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

void	swap(char **match_list, int i, int j)
{
	char *temp;

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

char	**wildcard_expand(const char *pattern, int *count, bool show_hidden, bool only_dir)
{
    DIR *dir;
    struct dirent *ent;
    char    **match_list;
	int		capacity;
	struct stat statbuf;
	
	capacity = 0;
    dir = opendir(".");
    if (!dir) 
        return (NULL);
    while (1)
    {
        ent = readdir(dir);
        if (ent == NULL)
            break;
		if (*(ent->d_name) == '.' && !show_hidden)
			continue ;
		if (stat(ent->d_name, &statbuf) != 0)
			return (NULL);
		if (only_dir && !S_ISDIR(statbuf.st_mode))
			continue ;
        if (matches(pattern, ent->d_name))
		{
            if ((*count) == capacity)
			{
				if (resize_list(&match_list, &capacity) == false)
					return (NULL);
			}
			if (only_dir)
				match_list[(*count)] = ft_strjoin(ent->d_name, "/");
			else
            	match_list[(*count)] = strdup(ent->d_name);
            if (!match_list[(*count)])
				return (free_list(match_list, (*count)), NULL);
            (*count)++;
        }
    }
    closedir(dir);
    if ((*count) == 0) {
        match_list = malloc(sizeof(char *));
		if (!match_list)
			return (NULL);
        match_list[0] = strdup(pattern);
        if (!match_list[0])
           return (free(match_list), NULL);
        (*count) = 1;
    }
    else
        sorter(match_list, *count);
    return (match_list);
}