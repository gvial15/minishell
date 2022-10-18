/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitdup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/06 13:25:33 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**splitdup(char **split)
{
	int		i;
	char	**new_split;

	if (!split)
		return (NULL);
	new_split = malloc(sizeof(char *) * split_len(split) + 1);
	i = -1;
	while (split[++i])
		new_split[i] = ft_strdup(split[i]);
	split[i] = 0;
	return (new_split);
}
