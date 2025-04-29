#include "minishell.h"

#define LOAD_FACTOR 0.75

static bool	create_item(t_ht_item **new_item, const char *key, const char *value)
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
	(*new_item)->value = ft_strdup(value);
	if (!(*new_item)->value)
	{
		free((*new_item)->key);
		free(*new_item);
		return (false);
	}
	return (true);
}

static int ht_reset(t_ht_item *node, const char *key, const char *value)
{
	while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
        {
            free(node->value);
            node->value = ft_strdup(value);
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
	t_ht_item       *node;
    unsigned long   index;
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
	else if(check == 0)
		return (true);
	create_item(&node, key, value);
    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    ht->count++;
	return (true);
}