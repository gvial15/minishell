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

#include "../ms.h"

char	*get_fd(char *cmd, char sign)
{
	char	*filename;
	int		start;
	int		i;

	start = 1;
	i = 0;
	while (cmd[i] && cmd[i] != sign)
		++i;
	while (cmd[i] == sign || cmd[i] == ' ')
		start = ++i;
	if (i == ft_strlen(cmd))
		return (NULL);
	while (cmd[i] && cmd[i] != ' ')
		i++;
	filename = ft_substr(cmd, start, i - start);
	return (filename);
}

char	**parse_args(char *cmd)
{
	char	**args;
	char	**split;
	int		i;
	int		j;
	int		arg_count;

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

void	get_cmds(char **envp, t_ms *ms)
{
	int		i;
	char	**split;
	t_cmd	*new_cmd;

	split = ft_split(ms->last_line, '|');
	i = -1;
	while (split[++i])
	{
		// TODO: manage environment variables eg. $> export test=4, $> echo $test, prints out 4
		// export var=value doesnt work inline with other pipes (|), must be alone on its line
		new_cmd = malloc(sizeof(t_cmd) * 1);
		new_cmd->fd_in = get_fd(split[i], '<');
		new_cmd->fd_out = get_fd(split[i], '>');
		new_cmd->cmd_path = get_cmd_path(split[i], envp);
		new_cmd->args = parse_args(split[i]);
		new_cmd->next = NULL;
		if (ms->cmds == NULL)
			ms->cmds = new_cmd;
		else
			lst_last(ms->cmds)->next = new_cmd;
	}
	free_split(split);
}
