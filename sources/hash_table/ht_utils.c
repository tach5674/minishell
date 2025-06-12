/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:31 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 17:18:10 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ht_free_node(t_ht_item *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

unsigned long	ht_hash(const char *key)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while (*key)
	{
		c = *key++;
		hash = ((hash << 5) + hash) + c;
	}
	return (hash);
}

bool	ht_resize(t_ht *ht)
{
	size_t			new_size;
	t_ht_item		**new_buckets;
	t_ht_item		*node;
	t_ht_item		*next;
	unsigned long	index;

	new_size = ht->size * 2;
	new_buckets = ft_calloc(new_size, sizeof(t_ht_item *));
	if (!new_buckets)
		return (false);
	while (ht->size--)
	{
		node = ht->buckets[ht->size];
		while (node)
		{
			next = node->next;
			index = ht_hash(node->key) % new_size;
			node->next = new_buckets[index];
			new_buckets[index] = node;
			node = next;
		}
	}
	free(ht->buckets);
	ht->buckets = new_buckets;
	return (ht->size = new_size, true);
}

void	ht_free(t_ht *ht)
{
	size_t		i;
	t_ht_item	*node;
	t_ht_item	*next;

	if (!ht)
		return ;
	i = 0;
	while (i < ht->size)
	{
		node = ht->buckets[i];
		while (node)
		{
			next = node->next;
			ht_free_node(node);
			node = next;
		}
		i++;
	}
	free(ht->buckets);
	free(ht);
}
