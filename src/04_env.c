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
			&& already_exist(get_varname_equal(args[i]), envp) >= 0)
			count++;
	return (count);
}

char	**unset_env_var(char **envp, char **args, t_ms *ms)
{
	int		i;
	int		j;
	int		var_count;
	char	**new_envp;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		return (envp);
	}
	var_count = unset_var_count(args, envp);
	if (var_count == 0)
		return (envp);
	new_envp = ft_calloc(split_len(envp) - var_count + 1, sizeof(char *));
	j = -1;
	i = -1;
	while (envp[++i])
		if (already_exist(get_varname_equal(envp[i]), args) == -1)
			new_envp[++j] = ft_strdup(envp[i]);
	free_split(envp);
	envp = NULL;
	return (new_envp);
}

static void	reassign(
	char **new_envp, char **args)
{
	int		i;
	int		arg_i;

	i = 0;
	while (args[++i])
	{
		arg_i = already_exist(get_varname_equal(args[i]), new_envp);
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
		if (valid_export(args[i], 1) && already_exist(get_varname_equal(args[i]), envp) == -1)
			count++;
	return (count);
}

char	**export_env_var(char **envp, char **args, t_ms *ms)
{
	int		i;
	int		j;
	char	**new_envp;
	int		var_count;

	if (split_len(args) == 1)
	{
		ms->err_last_child = 1;
		print_split(envp);
		return (envp);
	}
	var_count = export_var_count(args, envp);
	new_envp = ft_calloc((var_count + split_len(envp) + 1), sizeof(char *));
	split_cpy(envp, new_envp);
	reassign(new_envp, args);
	i = split_len(new_envp);
	j = 0;
	while (args[++j])
		if (valid_export(args[j], 0) && already_exist(get_varname_equal(args[j]), new_envp) == -1)
			new_envp[i++] = ft_strdup(args[j]);
	free_split(envp);
	envp = NULL;
	return (new_envp);
}
