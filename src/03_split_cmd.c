/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	new_i(char *cmd, int i)
{
	int	quote_nb;

	quote_nb = 1;
	while (cmd[++i])
	{
		if (is_quote(cmd[i]))
			quote_nb++;
		if ((quote_nb % 2 == 0 && cmd[i] == ' ')
			|| cmd[i + 1] == '\0')
			break ;
	}
	return (i);
}

static int	next_space_i(char *cmd, int i)
{
	while (cmd[++i])
		if (cmd[i] == ' ')
			break ;
	return (i);
}

static int	get_cmd_split_count(char *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (cmd[++i])
	{
		if (is_quote(cmd[i]))
		{
			i = new_i(cmd, i);
			count++;
		}
		else if ((i != 0 && cmd[i] == ' ' && cmd[i - 1] != ' ')
			|| (cmd[i + 1] == '\0' && cmd[i] != ' '))
			count++;
	}
	return (count);
}

char	**split_cmd(char *cmd)
{
	int		i;
	int		j;
	char	**cmd_split;

	cmd_split = ft_calloc(get_cmd_split_count(cmd) + 1, sizeof(char *));
	j = 0;
	i = -1;
	while (cmd[++i])
	{
		if (is_quote(cmd[i]))
		{
			if (cmd[new_i(cmd, i)] == ' ')
				cmd_split[j++] = ft_substr(cmd, i, new_i(cmd, i) - i);
			else
				cmd_split[j++] = ft_substr(cmd, i, new_i(cmd, i) - i + 1);
			i = new_i(cmd, i);
		}
		else if ((i != 0 && cmd[i] != ' ' && cmd[i - 1] == ' ')
				|| (i == 0 && cmd[i] != ' '))
		{
			cmd_split[j++] = ft_substr(cmd, i, next_space_i(cmd, i) - i);
			i = next_space_i(cmd, i);
		}
	}
	cmd_split[j] = 0;
	return (cmd_split);
}
