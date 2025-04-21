/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:53:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/11/13 19:59:27 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_char(char const *arr, char c)
{
	while (*arr)
	{
		if (*arr == c)
			return (1);
		arr++;
	}
	return (0);
}

static int	ft_trim_start_index(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_check_char(set, str[i]))
		++i;
	return (i);
}

static int	ft_trim_end_index(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_check_char(set, str[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start_index;
	int		end_index;
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start_index = ft_trim_start_index(s1, set);
	end_index = ft_trim_end_index(s1, set);
	if (start_index > end_index)
		len = 0;
	else
		len = end_index - start_index + 1;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = s1[start_index + i];
	res[i] = '\0';
	return (res);
}
