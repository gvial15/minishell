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

char	*get_varname_dollar(char *cmd)
{
	int		i;
	char	*varname;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '$')
			break ;
	varname = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
	return (varname);
}

static void	replace(char *cmd, char **envp)
{
	(void) envp;
	char	*varname;

	varname = get_varname_dollar(cmd);
	printf("%s\n", varname);
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
