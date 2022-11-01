/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_format_line.c                                   :+:      :+:    :+:   */
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
	if (last_line[i] == '|')
	{
		if (last_line[i - 1] != ' ' && last_line[i + 1] != ' ')
			return (2);
		if (last_line[i + 1] != ' ')
			return (3);
		if (last_line[i - 1] != ' ')
			return (1);
	}
	return (0);
}

static int	get_space_count(char *last_line)
{
	int	i;
	int	n_space;
	int	space_count;

	n_space = 0;
	space_count = 0;
	i = -1;
	while (last_line[++i])
	{
		if (is_quote(last_line[i]))
			i = new_i(last_line, i);
		n_space = need_space(last_line, i);
		if (n_space > 0)
		{
			space_count++;
			if (n_space == 2)
				space_count++;
		}
	}
	return (space_count);
}

static void	fill_new_line(char *n_last_line, char *last_line)
{
	int		i;
	int		j;
	int		in_quote;

	in_quote = -1;
	j = 0;
	i = -1;
	while (last_line[++i])
	{
		if (is_quote(last_line[i]) && in_quote == -1)
			in_quote = last_line[i];
		else if (last_line[i] == in_quote && in_quote != -1)
			in_quote = -1;
		if (need_space(last_line, i) && in_quote == -1)
		{
			if (need_space(last_line, i) == 1 || need_space(last_line, i) == 2)
				n_last_line[j++] = ' ';
			n_last_line[j++] = last_line[i];
			if (need_space(last_line, i) == 3 || need_space(last_line, i) == 2)
			n_last_line[j++] = ' ';
		}
		else
			n_last_line[j++] = last_line[i];
	}
}

// space out the redirections if needed ex: >out>>out2 = >out >>out2
// space out the pipes if needed ex: cat|cat|ls = cat | cat | ls
char	*format_line(char *last_line)
{
	int		space_count;
	char	*n_last_line;

	space_count = get_space_count(last_line);
	if (space_count == 0)
		return (last_line);
	n_last_line = ft_calloc(ft_strlen(last_line) + space_count + 1, sizeof(char));
	fill_new_line(n_last_line, last_line);
	free(last_line);
	return (n_last_line);
}
