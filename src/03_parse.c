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

static char	**get_fd_out(char *cmd)
{
	int		i;
	int		j;
	char	**fds;
	int		fd_count;
	char	**split;

	split = ft_split(cmd, ' ');
	fd_count = 0;
	i = -1;
	while (split[++i])
		if (split[i][0] == '>')
			fd_count++;
	fds = malloc(sizeof(char *) * fd_count + 1);
	j = 0;
	i = -1;
	while (split[++i])
	{
		if (i != 0 && *split[i - 1] == '>')
			fds[j++] = ft_strdup(split[i]);
		else if (*split[i] == '>' && ft_strlen(split[i]) > 1)
			fds[j++] = ft_strdup(&split[i][1]);
	}
	fds[j] = 0;
	free_split(split);
	return (fds);
}

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
		if (new_cmd->cmd_path)
			new_cmd->args = parse_args(split[i]);
		else
			new_cmd->args = NULL;
		new_cmd->fd_in = NULL;
		new_cmd->fd_out = get_fd_out(split[i]);
		new_cmd->next = NULL;
		if ((*data)->cmds == NULL)
			(*data)->cmds = new_cmd;
		else
			lst_last((*data)->cmds)->next = new_cmd;
	}
	free_split(split);
}
