/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:22:56 by gvial             #+#    #+#             */
/*   Updated: 2022/03/28 10:23:34 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	num_len(int value, int base)
{
	int	len;

	len = 0;
	if (value < 0)
	{
		if (base == 10)
			len++;
		value *= -1;
	}
	while (1)
	{
		value /= base;
		len++;
		if (value == 0)
			break ;
	}
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	int		len;
	int		neg;
	char	*num;
	char	*hex;

	neg = 0;
	len = num_len(value, base);
	if (value < 0)
	{
		value *= -1;
		if (base == 10)
			neg = 1;
	}
	hex = "0123456789abcdef";
	num = malloc(sizeof(char) * len + 1);
	num[len] = '\0';
	while (--len >= 0)
	{
		num[len] = hex[value % base];
		value /= base;
		if (len == 0 && neg == 1)
			num[len] = '-';
	}
	return (num);
}
