/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_fd_in_out_count(char **split)
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

void	create_fds(char **split, char **fds)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (split[++i])
	{
		if (i != 0 && split[i - 1][0] == '>' && ft_strlen(split[i - 1]) == 1)
			fds[j++] = ft_strdup(split[i]);
		if (split[i][0] == '>' && split[i][1] != '>' && ft_strlen(split[i]) > 1)
			fds[j++] = ft_strdup(&split[i][1]);
		if (i != 0 && ft_strnstr(split[i - 1], ">>", 2) && ft_strlen(split[i - 1]) == 2)
			fds[j++] = ft_strdup(split[i]);
		if (ft_strnstr(split[i], ">>", 2) && ft_strlen(split[i]) > 2)
			fds[j++] = ft_strdup(&split[i][2]);
	}
	fds[j] = 0;
}

static void	check_append(t_cmd *new_cmd, char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], ">", ft_strlen(split[i])))
		{
			if (ft_strnstr(split[i], ">>", 2))
				new_cmd->append = 1;
			else
				new_cmd->append = 0;
		}
	}
}

char	**get_fd_in_out(t_cmd *new_cmd, char *cmd, char sign)
{
	char	**fds;
	char	**split;

	new_cmd->append = 0;
	split = ft_split(cmd, ' ');
	fds = malloc(sizeof(char *) * get_fd_in_out_count(split) + 1);
	create_fds(split, fds);
	if (sign == '>')
		check_append(new_cmd, split);
	// if (sign == '<')
	// 	check_heredocs(new_cmd, split);
	free_split(split);
	return (fds);
}
