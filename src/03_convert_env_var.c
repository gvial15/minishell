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
/* ************************************************************************** */
#include "../include/minishell.h"

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

static int	get_dollar_i(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '$')
		break ;
	return (i);
}

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

static char	*replace(char *cmd, char **env)
{
	int		i;
	int		alr_exist;
	char	*str;
	char	*var_value;
	char	*new_cmd;

	str = get_varname_dollar(cmd);
	i = get_dollar_i(cmd);
	alr_exist = already_exist(str, env);
	if (alr_exist != -1)
	{
		// replace $var with it's value
	}
	else
	 	new_cmd = ft_substr(cmd, 0, i);
	return (new_cmd);
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
			cmd[i] = replace(cmd[i], envp);
}
