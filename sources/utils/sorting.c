/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:49:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 14:14:33 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// static int	ft_strcmp_bash(const char *s1, const char *s2)
// {
// 	int		i;
// 	char	c1;
// 	char	c2;

// 	i = 0;
// 	while (s1[i] && s2[i])
// 	{
// 		c1 = s1[i];
// 		c2 = s2[i];
// 		if (ft_tolower(c1) != ft_tolower(c2))
// 			return (ft_tolower(c1) - ft_tolower(c2));
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

static int	partition(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j], pivot) <= 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void	quicksort(char **arr, int low, int high)
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition(arr, low, high);
		quicksort(arr, low, pivot_index - 1);
		quicksort(arr, pivot_index + 1, high);
	}
}

void	sorter(char **match_list, int count)
{
	if (count > 1)
		quicksort(match_list, 0, count - 1);
}
