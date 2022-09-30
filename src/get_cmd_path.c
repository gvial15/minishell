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

#include "../ms.h"

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
	return (paths);
}

char	*isolate_cmd(char *cmd_brut)
{
	int		i;
	char	*cmd;
	char	**split;

	split = ft_split(cmd_brut, ' ');
	cmd = NULL;
	i = -1;
	while (split[++i])
	{
		if (!have_sign(split[i])
			&& ((i == 0) || (i != 0 && !have_sign(split[i - 1]))
				|| (i != 0 && have_sign(split[i - 1])
					&& ft_strlen(split[i - 1]) > 1)))
		{
			cmd = ft_strdup(split[i]);
			break ;
		}	
	}
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
		path = ft_strjoin(paths[i], cmd_without_args);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free(cmd_without_args);
	free_split(paths);
	return (path);
}
