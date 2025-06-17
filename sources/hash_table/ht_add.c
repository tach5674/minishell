/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:56:08 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 15:13:58 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	create_item(t_ht_item **new_item, const char *key,
		const char *value, bool only_exported)
{
	*new_item = malloc(sizeof(t_ht_item));
	if (!*new_item)
		return (false);
	(*new_item)->key = ft_strdup(key);
	if (!(*new_item)->key)
	{
		free(*new_item);
		return (false);
	}
	if (only_exported)
	{
		(*new_item)->value = NULL;
		(*new_item)->only_exported = only_exported;
		return (true);
	}
	(*new_item)->value = ft_strdup(value);
	if (!(*new_item)->value)
	{
		free((*new_item)->key);
		free(*new_item);
		return (false);
	}
	return (true);
}

static int	ht_reset(t_ht_item *node, const char *key, const char *value)
{
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(value);
			node->only_exported = false;
			if (!node->value)
				return (1);
			return (0);
		}
		node = node->next;
	}
	return (2);
}

bool	ht_add(t_ht *ht, const char *key, const char *value)
{
	t_ht_item		*node;
	unsigned long	index;
	int				check;

	node = NULL;
	if (!ht || !key || !value)
		return (false);
	if ((double)(ht->count + 1) / ht->size > LOAD_FACTOR)
		if (ht_resize(ht) == false)
			return (false);
	index = ht_hash(key) % ht->size;
	node = ht->buckets[index];
	check = ht_reset(node, key, value);
	if (check == 1)
		return (false);
	else if (check == 0)
		return (true);
	create_item(&node, key, value, false);
	node->next = ht->buckets[index];
	ht->buckets[index] = node;
	ht->count++;
	return (true);
}

bool	ht_add_no_value(t_ht *ht, const char *key)
{
	t_ht_item		*node;
	unsigned long	index;

	node = NULL;
	if (!ht || !key)
		return (false);
	if ((double)(ht->count + 1) / ht->size > LOAD_FACTOR)
		if (ht_resize(ht) == false)
			return (false);
	index = ht_hash(key) % ht->size;
	node = ht->buckets[index];
	create_item(&node, key, NULL, true);
	node->next = ht->buckets[index];
	ht->buckets[index] = node;
	ht->count++;
	return (true);
}
