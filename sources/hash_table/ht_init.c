/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:28 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/10 12:54:48 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define INITIAL_SIZE 64

static void	ht_init_error(t_ht *ht, char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	ht_free(ht);
	throw_err(MALLOC_ERROR);
}

static void	ht_init_add(t_ht *ht, char **envp, int i)
{
	char	*equal;
	char	*key;
	char	*value;
	size_t	key_len;

	key = NULL;
	value = NULL;
	equal = ft_strchr(envp[i], '=');
	if (equal)
	{
		key_len = equal - envp[i];
		key = ft_strndup(envp[i], key_len);
		if (!key)
			ht_init_error(ht, key, value);
		value = ft_strdup(equal + 1);
		if (!value)
			ht_init_error(ht, key, value);
		if (ht_add(ht, key, value) == false)
			ht_init_error(ht, key, value);
		free(key);
		free(value);
	}
}

t_ht *ht_init(char **envp)
{
    t_ht	*ht;
	int		i;
	
	ht = malloc(sizeof(t_ht));
    if (!ht)
        throw_err(MALLOC_ERROR);
    ht->size = INITIAL_SIZE;
    ht->count = 0;
    ht->buckets = ft_calloc(ht->size, sizeof(t_ht_item *));
    if (!ht->buckets)
    {
        ht_free(ht);
        throw_err(MALLOC_ERROR);
    }
    if (envp)
    {
        i = 0;
        while (envp[i])
        {
			ht_init_add(ht, envp, i);
            i++;
        }
    }
    return ht;
}

