/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:54:48 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/11/03 18:15:29 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scpy;
	size_t			i;

	i = -1;
	scpy = (unsigned char *) s;
	while (++i < n)
	{
		if (scpy[i] == (unsigned char)c)
			return (&scpy[i]);
	}
	return (NULL);
}
