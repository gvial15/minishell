/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/10/20 15:03:49 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	unset_var_count(char **args, char **envp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[++i])
		if (valid_unset(args[i], 1)
			&& already_exist(get_varname(args[i]), envp) >= 0)
			count++;
	return (count);
}

char	**unset_env_var(char **args, t_ms *ms)
{
	int		i;
	int		j;
	char	*varname;
	int		var_count;
	char	**new_envp;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		return (ms->envp);
	}
	var_count = unset_var_count(args, ms->envp);
	if (var_count == 0)
		return (ms->envp);
	new_envp = ft_calloc(split_len(ms->envp) - var_count + 1, sizeof(char *));
	j = -1;
	i = -1;
	while (ms->envp[++i])
	{
		varname = get_varname(ms->envp[i]);
		if (already_exist(varname, &args[1]) == -1)
			new_envp[++j] = ft_strdup(ms->envp[i]);
	}
	free_split(ms->envp);
	ms->envp = NULL;
	new_envp[++j] = 0;
	return (new_envp);
}

static void	reassign(char **new_envp, char **args)
{
	int		i;
	int		arg_i;

	i = 0;
	while (args[++i])
	{
		arg_i = already_exist(get_varname(args[i]), new_envp);
		if (arg_i != -1)
		{
			free(new_envp[arg_i]);
			new_envp[arg_i] = ft_strdup(args[i]);
		}
	}
}

static int	export_var_count(char **args, char **envp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[++i])
		if (valid_export(args[i], 1) && already_exist(get_varname(args[i]), envp) == -1)
			count++;
	return (count);
}

char	**export_env_var(char **args, t_ms *ms)
{
	int		i;
	int		j;
	char	**new_envp;
	int		var_count;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		export_print(ms->envp);
		return (ms->envp);
	}
	var_count = export_var_count(args, ms->envp);
	new_envp = ft_calloc((var_count + split_len(ms->envp) + 1), sizeof(char *));
	split_cpy(ms->envp, new_envp);
	reassign(new_envp, args);
	i = split_len(new_envp);
	j = 0;
	while (args[++j])
		if (valid_export(args[j], 0) && already_exist(get_varname(args[j]), new_envp) == -1)
			new_envp[i++] = ft_strdup(args[j]);
	free_split(ms->envp);
	ms->envp = NULL;
	return (new_envp);
}
