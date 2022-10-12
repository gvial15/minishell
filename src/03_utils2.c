/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:37:15 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/12 13:23:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//option 0: with double ptr -- 1:only inside
void	free_dbl_ptr(void **ptr, int option)
{
	int	i;

	if (ptr)
	{
		i = -1;
		while (ptr[++i])
			free(ptr[i]);
		if (option == 0)
			free(ptr);
	}
}
