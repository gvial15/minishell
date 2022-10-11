/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_varname(char *var)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	while (var[i] != '=')
		i++;
	varname = malloc(sizeof(char) * i);
	j = -1;
	while (++j < i)
		varname[j] = var[j];
	return (varname);
}

static int	already_exist(char *var, char **envp)
{
	int		i;
	char	*varname;

	varname = get_varname(var);
	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], varname, ft_strlen(varname))
			&& ft_strlen(get_varname(envp[i])) == ft_strlen(varname))
			return (1);
	return (0);
}

static int	is_valid(char *var, char **envp)
{
	int		i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '=' && i != 0)
			break ;
		if (i == 0 && (!ft_isalpha(var[i]) || var[i] == '='))
		{
			printf("export: '%s': not a valid identifier\n", var);
			return (0);
		}
	}
	if (!ft_strnstr(var, "=", ft_strlen(var)))
		return (0);
	if (already_exist(var, envp))
		return (0);
	return (1);
}

static int	var_count(char **args, char **envp)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[++i])
		if (is_valid(args[i], envp))
			count++;
	return (count);
}

int	get_env_len(char **envp)
{
	int	env_len;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	return (env_len);
}


//	still have to manage the reassignment of an already existing env var
char	**add_env_var(char **envp, char **args)
{
	int		i;
	int		j;
	char	**new_envp;
	int		var_count_;

	var_count_ = var_count(args, envp);
	if (!args || !var_count_)
		return (envp);
	new_envp = malloc(sizeof(char *) * (var_count_ + get_env_len(envp) + 1));
	j = 0;
	i = -1;
	while (envp[++i])
			new_envp[j++] = ft_strdup(envp[i]);
	i = -1;
	while (args[++i])
		if (is_valid(args[i], envp))
		new_envp[j++] = ft_strdup(args[i]);
	new_envp[j++] = 0;
	// free_split(envp); have to free envp
	return (new_envp);
}
