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

static char	*get_var_name(char *var)
{
	int		i;
	char	*varname;

	i = 0;
	while (var[i] && var[i] != ' ' && !is_quote(var[i]) && var[i] != '$')
		i++;
	varname = ft_substr(var, 0, i);
	return (varname);
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
		return (NULL);
	value = ft_substr(var, i + 1, ft_strlen(var) - i);
	return (value);
}

static int	env_var_i(char *cmd)
{
	int	i;
	int	single_quote;

	single_quote = 1;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == 39)
			single_quote *= -1;
		if (cmd[i] == '$' && single_quote == 1)
			if (cmd[i + 1] && !is_quote(cmd[i + 1]) && cmd[i + 1] != ' ')
				return (i);
	}
	return (-1);
}

static char	*replace(char *cmd, int var_i, t_ms *ms)
{
	char	*new_cmd;
	char	*varname;
	char	*varvalue;
	int		alr_exist;
	int		varname_len;

	new_cmd = ft_substr(cmd, 0, var_i);
	varname = get_var_name(&cmd[var_i + 1]);
	varname_len = ft_strlen(varname);
	alr_exist = already_exist(varname, ms->envp);
	if (alr_exist != -1)
		varvalue = get_var_value(ms->envp[alr_exist]);
	else
	 	varvalue = NULL;
	new_cmd = ft_strjoin_gnl(new_cmd, varvalue);
	if (varvalue)
		free(varvalue);
	new_cmd = ft_strjoin_gnl(new_cmd, &cmd[var_i + varname_len + 1]);
	free(cmd);
	return (new_cmd);
}

void	conv_env_var(char **cmd, t_ms *ms)
{
	int		i;
	int		var_i;

	i = -1;
	while (cmd[++i])
	{
		var_i = env_var_i(cmd[i]);
		while (var_i != -1)
		{
			cmd[i] = replace(cmd[i], var_i, ms);
			var_i = env_var_i(cmd[i]);
		}
	}
}
