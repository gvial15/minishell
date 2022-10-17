/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_get_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_fds_count(char **split, int sign)
{
	int	i;
	int	fd_count;

	fd_count = 0;
	i = -1;
	while (split[++i])
		if (split[i][0] == sign)
			fd_count++;
	return (fd_count);
}

static void	check_heredocs(t_cmd *new_cmd, char **split)
{
	int		i;
	int		j;

	new_cmd->heredoc = malloc(sizeof(int) * get_fds_count(split, '<') + 1);
	j = 0;
	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "<", ft_strlen(split[i])))
		{
			if (ft_strnstr(split[i], "<<", 2))
				new_cmd->heredoc[j++] = 1;
			else
				new_cmd->heredoc[j++] = 0;
		}
	}
	new_cmd->heredoc[j] = -1;
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

static void	create_fds(char **s, char **fds, int sign)
{
	int		i;
	int		j;
	char	*dbl;

	if (sign == '>')
		dbl = GREATER_THAN;
	if (sign == '<')
		dbl = LESSER_THAN;
	j = 0;
	i = -1;
	while (s[++i])
	{
		if (i != 0 && s[i - 1][0] == sign && ft_strlen(s[i - 1]) == 1)
			fds[j++] = remove_quotes(ft_strdup(s[i]));
		if (s[i][0] == sign && s[i][1] != sign && ft_strlen(s[i]) > 1)
			fds[j++] = remove_quotes(ft_strdup(&s[i][1]));
		if (i != 0 && ft_strnstr(s[i - 1], dbl, 2) && ft_strlen(s[i - 1]) == 2)
			fds[j++] = remove_quotes(ft_strdup(s[i]));
		if (ft_strnstr(s[i], dbl, 2) && ft_strlen(s[i]) > 2)
			fds[j++] = remove_quotes(ft_strdup(&s[i][2]));
	}
}

char	**get_fds(t_cmd *new_cmd, char *cmd, char sign)
{
	int		fds_count;
	char	**fds;
	char	**split;

	new_cmd->append = 0;
	split = ft_split(cmd, ' ');
	fds_count = get_fds_count(split, sign);
	if (fds_count == 0)
	{
		free_split(split);
		return (NULL);
	}
	fds = ft_calloc(fds_count + 1, sizeof(char *));
	create_fds(split, fds, sign);
	if (sign == '>')
		check_append(new_cmd, split);
	if (sign == '<')
		check_heredocs(new_cmd, split);
	free_split(split);
	return (fds);
}
