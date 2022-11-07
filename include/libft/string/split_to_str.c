/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*split_to_str(char **split, int free)
{
	int		i;
	char	*str;

	str = NULL;
	i = -1;
	while (split[++i])
		str = ft_strjoin_gnl(str, split[i]);
	if (free == 1)
		free_split(split);
	return (str);
}
