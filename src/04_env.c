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

char	**add_env_var(char **envp, char **args)
{
	int		i;
	int		j;
	char	**new_envp;
	int		var_count_;

	var_count_ = var_count(args, envp);
	if (!args || !var_count_)
		return (envp);
	new_envp = ft_calloc((var_count_ + split_len(envp) + 1), sizeof(char *));
	split_cpy(envp, new_envp);
	i = split_len(new_envp);
	j = 0;
	while (args[++j])
		if (is_valid(args[j], new_envp))
			new_envp[i++] = ft_strdup(args[j]);
	free_split(envp);
	return (new_envp);
}
