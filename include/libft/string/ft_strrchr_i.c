/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:55:41 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 11:27:03 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//Return the location(index)) of the last c in s. If no c in s, return -1
size_t	ft_strrchr_i(char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (s[i] != (char)c && i >= 0)
		i--;
	if (i >= 0 && s[i] == (char)c)
		return (i);
	else
		return (-1);
}
