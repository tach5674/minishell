/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:49:00 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/30 18:10:07 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HT_H
# define HT_H

# include "minishell.h"

typedef struct s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}						t_ht_item;

typedef struct s_ht
{
	t_ht_item			**buckets;
	size_t				size;
	size_t				count;
}						t_ht;

unsigned long			ht_hash(const char *key);
t_ht					*ht_init(char **envp);
bool					ht_add(t_ht *ht, const char *key, const char *value);
void					ht_unset(t_ht *ht, const char *key);
char					*ht_get(t_ht *ht, const char *key);
bool					ht_resize(t_ht *ht);
int						ht_print(t_ht *ht);
void					ht_free(t_ht *ht);
void					ht_free_node(t_ht_item *node);

#endif
