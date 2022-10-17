/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_convert_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:19 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:21 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */\

#include "../include/minishell.h"

static int	contain_env_var(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '$' && !is_quote(cmd[i + 1])
			&& cmd[i + 1] != ' ')
			return (1);
	return (0);
}

static char	*get_varname(char *cmd)
{
	(void) cmd;
	return (NULL);
}

static void	replace(char *cmd, char **envp)
{
	(void) envp;
	char	*varname;
	(void) varname;

	varname = get_varname(cmd);
}

// export var=2
// $var = 2
// $"var" = var
// "$var" = 2
// "$"var = $var
// echo grep$var = grep2
// <test grep$var = bash: grep2: command not found
void	convert_env_var(char **cmd, char **envp)
{
	int		i;

	i = -1;
	while (cmd[++i])
		if (contain_env_var(cmd[i]))
			replace(cmd[i], envp);
}
