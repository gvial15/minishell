/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:10 by gvial             #+#    #+#             */
/*   Updated: 2022/10/25 14:30:11 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_full_path(char **envp)
{
	int	i;
	int	path_exist;

	path_exist = 0;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path_exist = 1;
			break ;
		}
	}
	if (!path_exist)
		return (NULL);
	return (&envp[i][5]);
}

static char	**get_paths(char **envp)
{
	char	*full_path;
	char	**paths;
	int		i;

	full_path = get_full_path(envp);
	if (!full_path)
		return (NULL);
	paths = ft_split(full_path, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin_gnl(paths[i], "/");
	paths[i] = 0;
	return (paths);
}

static char	*find_path(char **paths, char *cmd_without_args)
{
	int		i;
	char	*path;

	i = -1;
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
	return (path);
}

char	*get_cmd_path(char **cmd, char **envp)
{
	int		cmd_i;
	char	*path;
	char	**paths;
	char	*cmd_without_args;

	cmd_i = find_cmd_i(cmd);
	path = NULL;
	if (cmd_i == -1)
		return (NULL);
	paths = get_paths(envp);
	if (!paths)
		return (ft_strdup(cmd[cmd_i]));
	cmd_without_args = ft_strdup(cmd[cmd_i]);
	cmd_without_args = remove_quotes(cmd_without_args);
	path = find_path(paths, cmd_without_args);
	free_split(paths);
	if (path == NULL)
		return (cmd_without_args);
	free(cmd_without_args);
	return (path);
}
