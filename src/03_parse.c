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

int	find_cmd_i(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (!have_redirec(split[i]))
		{
			if (i == 0)
				break;
			if (i > 1 && !have_redirec(split[i - 1]) && have_dbl_redirec(split[i - 2])
				&& ft_strlen(split[i - 2]) == 2)
				break ; // >> out cmd
			if (i > 1 && !have_redirec(split[i - 1]) && have_redirec(split[i - 2])
				&& ft_strlen(split[i - 2]) == 1)
				break ; // > out cmd
			if (have_redirec(split[i - 1]) && ft_strlen(split[i - 1]) > 1
				&& !have_dbl_redirec(split[i - 1]))
				break ; // >out cmd
			if (have_dbl_redirec(split[i - 1]) && ft_strlen(split[i - 1]) > 2)
				break ;	// >>out cmd
		}
	}
	return (i);
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
	while (split[++i] && !have_redirec(split[i]))
		arg_count++;
	if (arg_count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * arg_count + 1);
	j = -1;
	i = find_cmd_i(split);
	while (++j < arg_count)
		args[j] = ft_strdup(split[++i]);
	args[j] = 0;
	free_split(split);
	return (args);
}

static void	create_cmd_lst(t_ms *data, char **split, char **envp)
{
	int		i;
	t_cmd	*new_cmd;

	i = -1;
	while (split[++i])
	{
		new_cmd = malloc(sizeof(t_cmd) * 1);
		new_cmd->cmd_path = get_cmd_path(split[i], envp);
		new_cmd->args = parse_args(split[i]);
		new_cmd->heredoc = 0;
		new_cmd->append = 0;
		new_cmd->fd_in = get_fd_in_out(new_cmd, split[i], '<');
		new_cmd->fd_out = get_fd_in_out(new_cmd, split[i], '>');
		new_cmd->next = NULL;
		if (data->cmds == NULL)
			data->cmds = new_cmd;
		else
			lst_last(data->cmds)->next = new_cmd;
	}
}

// "<in" segfault
void	parse(char **envp, t_ms *data)
{
	char	**split;

	data->last_line = space_out_redirections(data->last_line);
	split = ft_split(data->last_line, '|');
	create_cmd_lst(data, split, envp);
	free_split(split);
}
