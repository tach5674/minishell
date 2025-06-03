/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:33 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/03 12:27:52 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ht_unset(t_ht *ht, const char *key)
{
	unsigned long	index;
	t_ht_item		*node;
	t_ht_item		*prev;

    if (!ht || !key)
        return;
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
            return;
        }
        prev = node;
        node = node->next;
    }
}

char *ht_get(t_ht *ht, const char *key)
{
    t_ht_item		*node;
	unsigned long	index;

    if (!ht || !key)
        return NULL;
    index = ht_hash(key) % ht->size;
    node = ht->buckets[index];
    while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

int	ht_print(t_ht *ht)
{
    size_t		i = 0;
    t_ht_item	*node;

    if (!ht)
        return (1);
    while (i < ht->size)
    {
        node = ht->buckets[i];
        while (node)
        {
            if (printf("%s=%s\n", node->key, node->value) == -1)
                return (-1);
            node = node->next;
        }
        i++;
    }
    return (0);
}

// char    **ht_to_envp(t_ht *ht, char **envp)
// {
//     int i;
// 	int	index;

// 	index = 0;
//     i = 0;
//     while (i < ht->count)
//     {
// 		if (ht->buckets[index])
// 		{
			
// 		}
//         envp[i] = ft_str_char_join()
//     }
// }