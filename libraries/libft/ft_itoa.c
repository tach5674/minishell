/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:03:21 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/11/01 13:44:45 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nlen(int n)
{
	int	count;
	int	ncpy;

	ncpy = n;
	count = 0;
	while (ncpy / 10)
	{
		++count;
		ncpy /= 10;
	}
	return (count + 1);
}

static void	ft_itoa_helper(char *res, int n, int nlen)
{
	if (n)
	{
		res[nlen - 1] = n % 10 + '0';
		ft_itoa_helper(res, n / 10, nlen - 1);
	}
}

char	*ft_itoa(int n)
{
	int		nlen;
	int		is_negative;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_negative = 0;
	if (n < 0)
		is_negative = 1;
	nlen = ft_count_nlen(n);
	res = (char *)malloc(sizeof(char) * (nlen + 1 + is_negative));
	if (!res)
		return (NULL);
	if (is_negative)
	{
		res[0] = '-';
		n = -n;
		++nlen;
	}
	ft_itoa_helper(res, n, nlen);
	res[nlen] = '\0';
	return (res);
}
