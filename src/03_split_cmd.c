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
	int		split_count;
	char	**cmd_split;

	split_count = get_cmd_split_count(cmd);
	cmd_split = ft_calloc(split_count + 1, sizeof(char *));
	j = 0;
	i = -1;
	while (cmd[++i])
	{
		if (is_quote(cmd[i]))
		{
			cmd_split[j++] = ft_substr(cmd, i, new_i(cmd, i) - i + 1);
			i = new_i(cmd, i);
		}
		if (i != 0 && cmd[i] != ' ' && cmd[i - 1] == ' ')
			cmd_split[j++] = ft_substr(cmd, i, 1);
	}
	cmd_split[j] = 0;
	return (cmd_split);
}
