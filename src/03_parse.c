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

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

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
}

char	**get_args(char **cmd)
{
	int		i;
	int		j;
	int		arg_count;
	char	**args;

	args = NULL;
	arg_count = 0;
	if (find_cmd_i(cmd) == -1)
		return (args);
	i = find_cmd_i(cmd);
	while (!have_redirec(cmd[++i]))
		arg_count++;
	args = ft_calloc((arg_count + 2), sizeof(char *));
	j = -1;
	i = find_cmd_i(cmd) - 1;
	while (!have_redirec(cmd[++i]))
		args[++j] = remove_quotes(ft_strdup(cmd[i]));
	return (args);
}

// export var=2
// $var = 2
// $"var" = var
// "$var" = 2
// "$"var = $var
// echo grep$var = grep2
// <test grep$var = bash: grep2: command not found
static void	create_cmd_lst(t_ms *ms, char **cmds, char **envp)
{
	int		i;
	t_cmd	*new_cmd;
	char	**cmd;

	i = -1;
	while (cmds[++i])
	{
		cmd = split_cmd(cmds[i]);
// 		manage $var convert_env_var(cmd);
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->cmd_path = get_cmd_path(cmd, envp);
		new_cmd->args = get_args(cmd);
		new_cmd->fd_in = get_fds(new_cmd, cmds[i], '<');
		new_cmd->fd_out = get_fds(new_cmd, cmds[i], '>');
		new_cmd->next = NULL;
		if (ms->cmds == NULL)
			ms->cmds = new_cmd;
		else
			lst_last(ms->cmds)->next = new_cmd;
		free(cmd);
	}
}

void	parse(char **envp, t_ms *ms)
{
	char	**cmds;

	ms->last_line = space_out_redirections(ms->last_line);
	cmds = ft_split(ms->last_line, '|');
	create_cmd_lst(ms, cmds, envp);
	free_split(cmds);
	free(ms->last_line);
}
