/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:08:08 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/02/10 17:13:42 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int symbol)
{
	return (symbol == ' ' || (symbol >= '\t' && symbol <= '\r'));
}

static char	*ft_trim_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	return (&str[i]);
}

int	ft_atoi(const char *nptr)
{
	int		result;
	char	*nptr_cpy;
	int		is_negative;

	result = 0;
	nptr_cpy = ft_trim_start((char *)nptr);
	is_negative = 1;
	if (*nptr_cpy == '-' || *nptr_cpy == '+')
	{
		if (*nptr_cpy == '-')
			is_negative = -1;
		++nptr_cpy;
	}
	while (ft_isdigit(*nptr_cpy))
	{
		result = result * 10 + (*nptr_cpy - 48);
		nptr_cpy++;
	}
	return (result * is_negative);
}
