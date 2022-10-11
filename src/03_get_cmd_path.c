/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:10 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:12 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_full_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	return (&envp[i][5]);
}

static char	**get_paths(char **envp)
{
	char	*full_path;
	char	**paths;
	int		i;

	full_path = get_full_path(envp);
	paths = ft_split(full_path, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin_gnl(paths[i], "/");
	paths[i] = 0;
	return (paths);
}

char	*isolate_cmd(char *cmd_brut)
{
	char	*cmd;
	char	**split;

	split = ft_split(cmd_brut, ' ');
	if (split_count(cmd_brut, ' ') == 1
		&& (*split[0] == '<' || *split[0] == '>'))
		cmd =  NULL;
	else
		cmd = ft_strdup(split[find_cmd_i(split)]);
	free_split(split);
	return (cmd);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*cmd_without_args;

	i = -1;
	paths = get_paths(envp);
	cmd_without_args = isolate_cmd(cmd);
	while (paths[++i])
	{
		if (cmd_without_args == NULL)
			break ;
		path = ft_strjoin(paths[i], cmd_without_args);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_split(paths);
	if (path == NULL)
		return (cmd_without_args);
	free(cmd_without_args);
	return (path);
}
