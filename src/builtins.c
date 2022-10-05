/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

char	**add_env_var(char **envp, char *var)
{
	char	**new_envp;
	int		i;
	int		j;
	
	if (*var == '=')
	{
		printf("export: '%s': not a valid identifier\n", var);
		return (envp);
	}
	if (*var != '=' && split_count(var, '=') < 2)
		return (envp);
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 3));
	j = -1;
	while (++j < i)
		new_envp[j] = ft_strdup(envp[j]);
	new_envp[j] = ft_strdup(var);
	new_envp[++j] = 0;
	free_split(envp);
	return (new_envp);
}
