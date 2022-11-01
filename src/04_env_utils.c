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

void	export_print(char **envp)
{
	int		i;
	char	*varname;
	char	*varvalue;

	i = -1;
	while (envp[++i])
	{
		varname = get_varname(envp[i]);
		varvalue = get_varvalue(envp[i]);
		printf("declare -x %s=\"%s\"\n", varname, varvalue);
		free(varname);
		free(varvalue);
	}
}

char	*get_varname(char *var)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	varname = ft_calloc(i + 1, sizeof(char));
	j = -1;
	while (++j < i)
		varname[j] = var[j];
	return (varname);
}

int	already_exist(char *varname, char **envp)
{
	int		i;
	char	*envp_varname;

	i = -1;
	while (envp[++i])
	{
		envp_varname = get_varname(envp[i]);
		if (ft_strnstr(envp[i], varname, ft_strlen(varname))
			&& ft_strlen(envp_varname) == ft_strlen(varname))
		{
			free(envp_varname);
			free(varname);
			return (i);
		}
		free(envp_varname);
	}
	free(varname);
	return (-1);
}

int	valid_unset(char *var, int err)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '=' || (i == 0 && ft_isdigit(var[i])))
		{
			if (err)
				printf("unset: `%s': not a valid identifier\n", var);
			return (0);
		}
	}
	return (1);
}

int	valid_export(char *var, int err)
{
	int		i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '=' && i != 0)
			break ;
		if (i == 0 && (!ft_isalpha(var[i]) || var[i] == '='))
		{
			if (err)
				printf("export: '%s': not a valid identifier\n", var);
			return (0);
		}
	}
	if (!ft_strnstr(var, "=", ft_strlen(var)))
		return (0);
	return (1);
}
