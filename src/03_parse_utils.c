/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:28 by gvial             #+#    #+#             */
/*   Updated: 2022/10/07 17:36:57 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	have_redirec(char *s)
{
	if (s == NULL)
		return (1);
	if (s[0] == '<' || s[0] == '>')
		return (1);
	return (0);
}

int	have_dbl_redirec(char *s)
{
	if (ft_strnstr(s, ">>", 2) || ft_strnstr(s, "<<", 2))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	int		nb_quotes;
	char	*new_s;

	if (!s)
		return (NULL);
	nb_quotes = 0;
	i = -1;
	while (s[++i])
		if (is_quote(s[i]))
			nb_quotes++;
	if (nb_quotes == 0)
		return (s);
	new_s = ft_calloc(ft_strlen(s) - (nb_quotes), sizeof(char));
	j  = -1;
	i  = -1;
	while (s[++i])
		if (!is_quote(s[i]))
			new_s[++j] = s[i];
	new_s[++j] = 0;
	free(s);
	return (new_s);
}

int	find_cmd_i(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!have_redirec(s[i]))
		{
			if (i == 0)
				break ;
			if (i > 1 && !have_redirec(s[i - 1]) && have_dbl_redirec(s[i - 2])
				&& ft_strlen(s[i - 2]) == 2)
				break ;
			if (i > 1 && !have_redirec(s[i - 1]) && have_redirec(s[i - 2])
				&& ft_strlen(s[i - 2]) == 1)
				break ;
			if (have_redirec(s[i - 1]) && ft_strlen(s[i - 1]) > 1
				&& !have_dbl_redirec(s[i - 1]))
				break ;
			if (have_dbl_redirec(s[i - 1]) && ft_strlen(s[i - 1]) > 2)
				break ;
		}
		if (i == (int)ft_strlen(s[i]))
			i = -1;
	}
	return (i);
}
