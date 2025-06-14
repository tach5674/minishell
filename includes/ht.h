/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:49:00 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 11:25:36 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HT_H
# define HT_H

# include "minishell.h"

# define LOAD_FACTOR 0.75
# define INITIAL_SIZE 64

unsigned long	ht_hash(const char *key);
t_ht			*ht_init(char **envp);
bool			ht_add(t_ht *ht, const char *key, const char *value);
void			ht_unset(t_ht *ht, const char *key);
char			*ht_get(t_ht *ht, const char *key);
bool			ht_resize(t_ht *ht);
int				ht_print(t_ht *ht);
void			ht_free(t_ht *ht);
void			ht_free_node(t_ht_item *node);
char			**ht_to_envp(t_ht *ht);
int             print_export_line(char *str);
#endif
