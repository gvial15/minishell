/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_pipe(char *s)
{
	if (s[0] == '|' && ft_strlen(s) == 1)
		return (1);
	return (0);
}

static int	get_cmds_count(char **cmds)
{
	int	i;
	int	count;

	count = 1;
	i = -1;
	while (cmds[++i])
		if (is_pipe(cmds[i]))
			count++;
	return (count);
}

char	**split_cmds(char **cmds)
{
	int		i;
	int		j;
	char	**splitted_cmds;

	splitted_cmds = ft_calloc(get_cmds_count(cmds) + 1, sizeof(char *));
	j = 0;
	i = -1;
	while (cmds[++i])
	{
		if (!is_pipe(cmds[i]))
		{
			splitted_cmds[j] = ft_strjoin_gnl(splitted_cmds[j], cmds[i]);
			if (cmds[i + 1] != 0)
				splitted_cmds[j] = ft_strjoin_gnl(splitted_cmds[j], " ");
		}
		if (is_pipe(cmds[i]))
			j++;
	}
	free_split(cmds);
	return (splitted_cmds);
}
