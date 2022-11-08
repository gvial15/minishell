/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/10/20 15:03:49 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**remove_one(char **envp, char *varname)
{
	int		i;
	int		j;
	char	*env_varname;
	char	**new_envp;

	new_envp = ft_calloc(split_len(envp), sizeof(char *));
	j = -1;
	i = -1;
	while (envp[++i])
	{
		env_varname = get_varname(envp[i]);
		if (ft_strnstr(env_varname, varname, \
			ft_strlen(env_varname) + ft_strlen(varname))
			&& ft_strlen(env_varname) == ft_strlen(varname));
		else
			new_envp[++j] = ft_strdup(envp[i]);
		free(env_varname);
	}
	free_split(envp);
	return (new_envp);
}

char	**unset_env_var(char **args, t_ms *ms)
{
	int		i;
	char	**new_envp;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		return (ms->envp);
	}
	new_envp = splitdup(ms->envp);
	free_split(ms->envp);
	i = -1;
	while (args[++i])
	{
		if (valid_unset(args[i], 1)
			&& already_exist(ft_strdup(args[i]), new_envp) != -1)
			new_envp = remove_one(new_envp, args[i]);
	}
	return (new_envp);
}
