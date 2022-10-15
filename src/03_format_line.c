/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	need_space(char *last_line, int i)
{
	if (i != 0 && (last_line[i] == '>' || last_line[i] == '<'))
		if (last_line[i - 1] != ' ' && !have_redirec(&last_line[i - 1])
			&& !is_quote(last_line[i - 1]))
			return (1);
	return (0);
}

static int	get_space_count(char *last_line)
{
	int	i;
	int	space_count;

	space_count = 0;
	i = -1;
	while (last_line[++i])
		if (need_space(last_line, i))
			space_count++;
	return (space_count);
}

// space out the redirections if needed ex: ">out>>out2" = ">out >>out2"
char	*space_out_redirections(char *last_line)
{
	int		i;
	int		j;
	int		space_count;
	char	*n_last_line;

	space_count = get_space_count(last_line);
	if (space_count == 0)
		return (last_line);
	n_last_line = malloc(sizeof(char) * ft_strlen(last_line) + space_count + 1);
	j = 0;
	i = -1;
	while (last_line[++i])
	{
		if (need_space(last_line, i))
		{
			n_last_line[j++] = ' ';
			n_last_line[j++] = last_line[i];
		}
		else
			n_last_line[j++] = last_line[i];
	}
	n_last_line[j] = 0;
	free(last_line);
	return (n_last_line);
}
