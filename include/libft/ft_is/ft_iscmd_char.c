/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscmd_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:11:11 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/07 13:20:07 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//return 0 if space or < or >
int	ft_iscmd_char(char c)
{
	if ((c >= 9 && c <= 13) || c == 32 || c == '<' || c == '>')
		return (0);
	return (1);
}

//return 1 if all space or < or > -1 if NULL or empty -0 is not
int	ft_isallcmd_char(char *str)
{
	int	i;

	if (!str || ft_strlen(str) == 0)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (ft_iscmd_char(str[i]) == 1)
			return (0);
	}
	return (1);
}

//return 0 if space
int	ft_isspace_r(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (0);
	return (1);
}

//return 1 if all space -1 if NULL or empty -0 is not
int	ft_isallspace(char *str)
{
	int	i;

	if (!str || ft_strlen(str) == 0)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (ft_isspace_r(str[i]) == 1)
			return (0);
	}
	return (1);
}
