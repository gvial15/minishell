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

static char	*get_env_varname(char *cmd)
{
	int		i;
	char	*varname;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '$')
			break ;
	varname = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
	varname = remove_quotes(varname);
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

static char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i= -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (var[i + 1] == 0)
		return (NULL);;
	value = ft_substr(var, i + 1, ft_strlen(var) - i);
	return (value);
}

// export t=2
// "hello$t yoo"
static char	*replace(char *cmd, char **env)
{
	int		i;
	int		alr_exist;
	char	*varname;
	char	*s;
	char	*new_cmd;

	new_cmd = NULL;
	i = get_dollar_i(cmd);
	if (i > 0)
		new_cmd = ft_substr(cmd, 0, i);
	varname = get_env_varname(cmd);
	alr_exist = already_exist(varname, env);
	if (alr_exist != -1)
	{
		s = get_var_value(env[alr_exist]);
		new_cmd = ft_strjoin_gnl(new_cmd, s);
		free(s);
	}
	return (new_cmd);
}

void	convert_env_var(char **cmd, char **envp)
{
	int		i;
	int		j;

	j = -1;
	i = -1;
	while (cmd[++i])
	{
		while (cmd[i][++j])
			if (cmd[i][j] == '$' && !is_quote(cmd[i][j + 1])
				&& cmd[i][j + 1] != ' ')
				cmd[i] = replace(cmd[i], envp);
		j = -1;
	}
}
