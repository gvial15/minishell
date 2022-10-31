/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/10/25 13:16:30 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	new_i(char *cmd, int i)
{
	int		quote_nb;
	char	quote_type;

	quote_type = cmd[i];
	quote_nb = 1;
	while (cmd[++i])
	{
		if (cmd[i] == quote_type)
			quote_nb++;
		if ((quote_nb % 2 == 0 && cmd[i] == ' ')
			|| cmd[i + 1] == '\0')
			break ;
	}
	return (i);
}

static int	cmd_split_count(char *cmd)
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

static int	parse_block(char **new_cmd, char *cmd, int i)
{
	char	in_quote;
	int		start;
	int		new_i;

	start = i;
	in_quote = -1;
	while (cmd[i])
	{
		new_i = i;
		if (cmd[i] == in_quote)
			in_quote = -1;
		else if (is_quote(cmd[i]) && in_quote == -1)
			in_quote = cmd[i];
		if (in_quote == -1 && (cmd[i + 1] == ' ' || cmd[i + 1] == '\0'))
		{
			*new_cmd = ft_substr(cmd, start, i - start + 1);
			break ;
		}
		i++;
	}
	return (new_i);
}

char	**split_quotes(char *cmd)
{
	int		i;
	int		j;
	char	**cmd_split;

	cmd_split = ft_calloc(cmd_split_count(cmd) + 1, sizeof(char *));
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
				i = parse_block(&cmd_split[j++], cmd, i);
	}
	cmd_split[cmd_split_count(cmd)] = NULL;
	return (cmd_split);
}
