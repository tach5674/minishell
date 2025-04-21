/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:14:56 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/02/15 15:20:54 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstnew(int data, size_t index)
{
	t_stack	*nnode;

	nnode = (t_stack *)malloc(sizeof(t_stack));
	if (!nnode)
		return (NULL);
	nnode->data = data;
	nnode->index = index;
	nnode->next = NULL;
	return (nnode);
}
