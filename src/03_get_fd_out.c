/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_fdout_count(char **split)
{
	int	i;
	int	fd_count;

	fd_count = 0;
	i = -1;
	while (split[++i])
		if (split[i][0] == '>')
			fd_count++;
	return (fd_count);
}

// problem with "">> out"
char	**get_fd_out(t_cmd **new_cmd, char *cmd)
{
	int		i;
	int		j;
	char	**fds;
	char	**split;

	(*new_cmd)->append = 0;
	split = ft_split(cmd, ' ');
	fds = malloc(sizeof(char *) * get_fdout_count(split) + 1);
	j = 0;
	i = -1;
	while (split[++i])
	{
		if (i != 0 && *split[i - 1] == '>' && ft_strlen(split[i - 1]) == 1)
			fds[j++] = ft_strdup(split[i]);
		else if (split[i][0] == '>' && ft_strlen(split[i]) > 1)
			fds[j++] = ft_strdup(&split[i][1]);
	}
	if (fds[j -1][0] == '>')
		(*new_cmd)->append = 1;
	fds[j] = 0;
	// need to reformat double (>>) fd_out
	return (fds);
}
