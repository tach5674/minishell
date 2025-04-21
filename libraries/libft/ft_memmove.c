/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:40 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/10/26 14:22:29 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cpy;
	unsigned char	*src_cpy;

	dest_cpy = (unsigned char *) dest;
	src_cpy = (unsigned char *) src;
	if (!src_cpy && !dest_cpy)
		return (NULL);
	if (dest_cpy < src_cpy)
		while (n--)
			*dest_cpy++ = *src_cpy++;
	else
	{
		dest_cpy += n;
		src_cpy += n;
		while (n--)
			*(--dest_cpy) = *(--src_cpy);
	}
	return (dest);
}
