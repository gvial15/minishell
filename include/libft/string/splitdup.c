/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 14:53:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**splitdup(char **split)
{
	int		i;
	char	**new_split;

	if (!split)
		return (NULL);
	new_split = ft_calloc(split_len(split) + 1, sizeof(char *));
	i = -1;
	while (split[++i])
		new_split[i] = ft_strdup(split[i]);
	new_split[i] = 0;
	return (new_split);
}
