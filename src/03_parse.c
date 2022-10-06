/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/10/05 15:02:30 by mraymond         ###   ########.fr       */
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

void	create_cmd_lst(t_ms **data, char **split, char **envp)
{
	int		i;
	t_cmd	*new_cmd;

	i = -1;
	while (split[++i])
	{
		new_cmd = malloc(sizeof(t_cmd) * 1);
		new_cmd->cmd_path = get_cmd_path(split[i], envp);
		if (new_cmd->cmd_path)
			new_cmd->args = parse_args(split[i]);
		else
			new_cmd->args = NULL;
		new_cmd->heredoc = 0;
		new_cmd->fd_in = NULL;
		new_cmd->fd_out = get_fd_out(&new_cmd, split[i]);
		new_cmd->next = NULL;
		if ((*data)->cmds == NULL)
			(*data)->cmds = new_cmd;
		else
			lst_last((*data)->cmds)->next = new_cmd;
	}
}

void	parse(char **envp, t_ms **data)
{
	char	**split;
	split = ft_split((*data)->last_line, '|');
	create_cmd_lst(data, split, envp);
	free_split(split);
}
