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

static char	**add_one(char **envp, char *var)
{
	int		len;
	char	**new_envp;

	len = split_len(envp);
	new_envp = ft_calloc(len + 2, sizeof(char *));
	split_cpy(envp, new_envp);
	new_envp[len] = ft_strdup(var);
	free_split(envp);
	return (new_envp);
}

static char	*reassign (char *var, char *arg)
{
	char	*new_var;

	new_var = ft_strdup(arg);
	free(var);
	return (new_var);
}

static char	**export(char **envp, char **args)
{
	int		i;
	int		alr_exist;
	char	**new_envp;

	new_envp = splitdup(envp);
	i = -1;
	while (args[++i])
	{
		if (valid_export(args[i], 1))
		{
			alr_exist = already_exist(get_varname(args[i]), new_envp);
			if (alr_exist != -1)
				new_envp[alr_exist] = reassign(new_envp[alr_exist], args[i]);
			else
				new_envp = add_one(new_envp, args[i]);
		}
	}
	return (new_envp);
}

char	**export_env_var(char **args, t_ms *ms)
{
	char	**new_envp;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		export_print(ms->envp);
		return (ms->envp);
	}
	new_envp = export(ms->envp, args);
	free_split(ms->envp);
	return (new_envp);
}
