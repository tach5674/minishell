/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:24:55 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/11/14 14:33:29 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	while (dst_len < dsize && dst[dst_len])
		dst_len++;
	src_len = ft_strlen(src);
	i = 0;
	while ((i + dst_len + 1) < dsize && src[i])
	{
		dst[i + dst_len] = src[i];
		++i;
	}
	if (dst_len != dsize)
		dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}
