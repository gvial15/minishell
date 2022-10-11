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

//	still have to manage the reassignment of an already existing env var
char	**add_env_var(char **envp, char **args)
{
	// int		i;
	// int		j;
	char	**new_envp;
	int		var_count_;

	var_count_ = var_count(args, envp);
	if (!args || !var_count_)
		return (envp);
	new_envp = malloc(sizeof(char *) * (var_count_ + get_env_len(envp) + 1));
//	fill up the new_envp with envp while looking for
//	the already_there vars to overwrite them

//	fill up the remaining of new_envp with new vars but skip the already_there ones

//	free_split(envp); have to free envp
	return (new_envp);
}
