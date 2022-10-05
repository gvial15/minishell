/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:18:42 by gvial             #+#    #+#             */
/*   Updated: 2022/08/04 15:19:59 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bubble_sort(int *tab, unsigned int size)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (++i < (int)size)
	{
		j = -1;
		while (++j < (int)size - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}
