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

int	find_cmd_i(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!have_redirec(s[i]))
		{
			if (i == 0)
				break ;
			if (i > 1 && !have_redirec(s[i - 1]) && have_dbl_redirec(s[i - 2])
				&& ft_strlen(s[i - 2]) == 2)
				break ;
			if (i > 1 && !have_redirec(s[i - 1]) && have_redirec(s[i - 2])
				&& ft_strlen(s[i - 2]) == 1)
				break ;
			if (have_redirec(s[i - 1]) && ft_strlen(s[i - 1]) > 1
				&& !have_dbl_redirec(s[i - 1]))
				break ;
			if (have_dbl_redirec(s[i - 1]) && ft_strlen(s[i - 1]) > 2)
				break ;
		}
	}
	return (i);
}

char	**parse_args(char *cmd)
{
	int		i;
	int		j;
	int		arg_count;
	char	**args;
	char	**split;

	args = NULL;
	arg_count = 0;
	split = ft_split(cmd, ' ');
	if (isolate_cmd(cmd) == NULL)
		return (args);
	i = find_cmd_i(split);
	while (!have_redirec(split[++i]))
		arg_count++;
	args = ft_calloc((arg_count + 2), sizeof(char *));
	j = -1;
	i = find_cmd_i(split) - 1;
	while (!have_redirec(split[++i]))
		args[++j] = ft_strdup(split[i]);
	free_split(split);
	return (args);
}

static void	create_cmd_lst(t_ms *ms, char **cmds, char **envp)
{
	int		i;
	t_cmd	*new_cmd;
	char	**cmd;

	i = -1;
	while (cmds[++i])
	{
		cmd = split_cmd(cmds[i]);
		(void)	cmd;
		new_cmd = ft_calloc(1, sizeof(t_cmd));
		new_cmd->cmd_path = get_cmd_path(cmds[i], envp);
		new_cmd->args = parse_args(cmds[i]);
		new_cmd->heredoc = 0;
		new_cmd->append = 0;
		new_cmd->fd_in = get_fds(new_cmd, cmds[i], '<');
		new_cmd->fd_out = get_fds(new_cmd, cmds[i], '>');
		new_cmd->next = NULL;
		if (ms->cmds == NULL)
			ms->cmds = new_cmd;
		else
			lst_last(ms->cmds)->next = new_cmd;
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
