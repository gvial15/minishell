/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmds(t_ms *ms)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = ms->cmds;
	if (cmd == NULL)
		return ;
	while (cmd)
	{
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->fd_in)
			free_split(cmd->fd_in);
		if (cmd->fd_out)
			free_split(cmd->fd_out);
		if (cmd->heredoc)
			free(cmd->heredoc);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	ms->cmds = NULL;
}

char	**get_args(char **cmd)
{
	int		i;
	int		j;
	int		arg_count;
	char	**args;

	args = NULL;
	i = find_cmd_i(cmd);
	if (i == -1)
		return (NULL);
	if (i == split_len(cmd))
		return (&cmd[i - 1]);
	arg_count = 0;
	while (!have_redirec(cmd[++i]))
		arg_count++;
	args = ft_calloc((arg_count + 2), sizeof(char *));
	j = -1;
	i = find_cmd_i(cmd) - 1;
	while (!have_redirec(cmd[++i]))
		args[++j] = remove_quotes(ft_strdup(cmd[i]));
	return (args);
}

static void	create_cmd_lst(t_ms *ms, char **cmds)
{
	int		i;
	t_cmd	*new_cmd;
	char	**cmd;

	cmd = NULL;
	i = -1;
	while (cmds[++i])
	{
		cmd = split_quotes(cmds[i]);
		convert_env_var(cmd, ms->envp);
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->cmd_path = get_cmd_path(cmd, ms->envp);
		new_cmd->args = get_args(cmd);
		new_cmd->fd_in = get_fds(new_cmd, cmd, '<');
		new_cmd->fd_out = get_fds(new_cmd, cmd, '>');
		new_cmd->next = NULL;
		if (ms->cmds == NULL)
			ms->cmds = new_cmd;
		else
			lst_last(ms->cmds)->next = new_cmd;
		free(cmd);
	}
}

void	parse(t_ms *ms)
{
	char	**cmds;

	ms->last_line = space_out_redirections(ms->last_line);
	cmds = split_quotes(ms->last_line);
	cmds = split_cmds(cmds);
	create_cmd_lst(ms, cmds);
	free_split(cmds);
	free(ms->last_line);
	ms->last_line = NULL;
}
