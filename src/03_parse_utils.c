/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	have_redirec(char *s)
{
	if (!s)
		return (0);
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

static int	get_nb_quote(char *s)
{
	int	i;
	int	nb_quote;

	nb_quote = 0;
	i = -1;
	while (s[++i])
	{
		if (is_quote(s[i]))
		{
			i = new_i(s, i) - 1;
			nb_quote++;
		}
	}
	return (nb_quote);
}

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	int		nb_quote;
	char	first_quote;
	char	*new_s;

	nb_quote = get_nb_quote(s);
	if (!nb_quote)
		return (s);
	i = 0;
	while (!is_quote(s[i]))
		i++;
	first_quote = s[i];
	new_s = ft_calloc(ft_strlen(s) - nb_quote + 1, sizeof(char));
	j = -1;
	i = -1;
	while (s[++i])
		if (s[i] != first_quote)
			new_s[++j] = s[i];
	free(s);
	return (new_s);
}

int	find_cmd_i(char **s)
{
	int	i;

	i = 0;
	while (s[i])
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
		if (s[i + 1] == 0)
		{
			i = -1;
			break ;
		}
		i++;
	}
	return (i);
}
