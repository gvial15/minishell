/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_conv_env_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:57:32 by gvial             #+#    #+#             */
/*   Updated: 2022/10/25 18:57:34 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_env_varname(char *cmd)
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

int	get_dollar_i(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '$')
		break ;
	return (i);
}

char	*get_var_value(char *var)
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