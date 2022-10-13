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

void	reassign(char **new_envp, char **args)
{
	int		i;
	int		arg_i;

	i = 0;
	while (args[++i])
	{
		arg_i = already_exist(args[i], new_envp);
		if (arg_i != -1)
		{
			free(new_envp[arg_i]);
			new_envp[arg_i] = ft_strdup(args[i]);
		}
	}
}

char	*get_varname(char *var)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	while (var[i] != '=')
		i++;
	varname = ft_calloc(i, sizeof(char));
	j = -1;
	while (++j < i)
		varname[j] = var[j];
	return (varname);
}

int	already_exist(char *var, char **envp)
{
	int		i;
	char	*varname;
	char	*get_var_name_;

	varname = get_varname(var);
	i = -1;
	while (envp[++i])
	{
		get_var_name_ = get_varname(envp[i]);
		if (ft_strnstr(envp[i], varname, ft_strlen(varname))
			&& ft_strlen(get_var_name_) == ft_strlen(varname))
		{
			free(get_var_name_);
			free(varname);
			return (i);
		}
		free(get_var_name_);
	}
	free(varname);
	return (-1);
}

int	is_valid(char *var, char **envp)
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
	if (already_exist(var, envp) != -1)
		return (0);
	return (1);
}

int	var_count(char **args, char **envp)
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
