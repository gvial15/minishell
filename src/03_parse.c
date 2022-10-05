/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse_args(char *cmd)
{
	char	**args;
	char	**split;
	int		i;
	int		j;
	int		arg_count;

	args = NULL;
	split = ft_split(cmd, ' ');
	arg_count = 0;
	i = find_cmd_i(split);
	while (split[++i] && !have_sign(split[i]))
		arg_count++;
	args = malloc(sizeof(char *) * arg_count + 1);
	j = -1;
	i = find_cmd_i(split);
	while (++j < arg_count)
		args[j] = ft_strdup(split[++i]);
	args[j] = 0;
	free_split(split);
	return (args);
}

void	parse(char **envp, t_ms **data)
{
	int		i;
	char	**split;
	t_cmd	*new_cmd;

	split = ft_split((*data)->last_line, '|');
	i = -1;
	while (split[++i])
	{
		new_cmd = malloc(sizeof(t_cmd) * 1);
		new_cmd->cmd_path = get_cmd_path(split[i], envp);
		new_cmd->args = parse_args(split[i]);
		new_cmd->fd_in = NULL;
		new_cmd->fd_out = NULL;
		new_cmd->next = NULL;
		if ((*data)->cmds == NULL)
			(*data)->cmds = new_cmd;
		else
			lst_last((*data)->cmds)->next = new_cmd;
	}
	free_split(split);
}
