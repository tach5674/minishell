/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:56:27 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:03 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ht_unset(t_ht *ht, const char *key)
{
	unsigned long	index;
	t_ht_item		*node;
	t_ht_item		*prev;

	if (!ht || !key)
		return ;
	index = ht_hash(key) % ht->size;
	node = ht->buckets[index];
	prev = NULL;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				ht->buckets[index] = node->next;
			ht_free_node(node);
			ht->count--;
			return ;
		}
		prev = node;
		node = node->next;
	}
}

char	*ht_get(t_ht *ht, const char *key)
{
	t_ht_item		*node;
	unsigned long	index;

	if (!ht || !key)
		return (NULL);
	index = ht_hash(key) % ht->size;
	node = ht->buckets[index];
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int	ht_print(t_ht *ht)
{
	size_t		i;
	t_ht_item	*node;

	i = 0;
	if (!ht)
		return (1);
	while (i < ht->size)
	{
		node = ht->buckets[i];
		while (node)
		{
			if (node->only_exported == true)
			{
				node = node->next;
				continue ;
			}
			if (printf("%s=%s\n", node->key, node->value) == -1)
				return (-1);
			node = node->next;
		}
		i++;
	}
	return (0);
}

static bool	item_to_envp(char **envp, t_ht_item *item, int j)
{
	if (item->only_exported)
	{
		envp[j] = ft_strdup(item->key);
		if (!envp[j])
		{
			free_split(envp);
			return (false);
		}
		return (true);
	}
	envp[j] = ft_str_char_join(item->key, item->value, '=');
	if (!envp[j])
	{
		free_split(envp);
		return (false);
	}
	return (true);
}

char	**ht_to_envp(t_ht *ht, bool export)
{
	size_t		i;
	size_t		j;
	t_ht_item	*item;
	char		**envp;

	envp = malloc((ht->count + 1) * sizeof(char *));
	if (!envp)
		return (perror("minishell"), NULL);
	i = 0;
	j = 0;
	while (i < ht->size)
	{
		item = ht->buckets[i];
		while (item)
		{
			if (item->only_exported == true && export == false)
			{
				item = item->next;
				continue ;
			}
			if (item_to_envp(envp, item, j) == false)
				return (perror("minishell"), NULL);
			item = item->next;
			j++;
		}
		i++;
	}
	envp[j] = NULL;
	return (envp);
}
