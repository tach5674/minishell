/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:33:51 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/10/26 14:00:57 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_cpy;
	unsigned char	*dest_cpy;

	i = -1;
	src_cpy = (unsigned char *) src;
	dest_cpy = (unsigned char *) dest;
	if (!src_cpy && !dest_cpy)
		return (NULL);
	while (++i < n)
		dest_cpy[i] = src_cpy[i];
	return (dest);
}
