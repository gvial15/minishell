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
#include <string.h>

static char	*replace(char *cmd, char **env, t_ms *ms)
{
	char	*new_cmd;
	char	*varname;
	char	*replace_value;
	int		alr_exist;

	new_cmd = ft_substr(cmd, 0, get_dollar_i(cmd));
	varname = get_env_varname(cmd);
	if (ft_strnstr(varname, "?", 1))
		replace_value = ft_itoa(ms->err_last_child);
	alr_exist = already_exist(varname, env);
	if (alr_exist != -1)
	 	replace_value = get_var_value(env[alr_exist]);
	new_cmd = ft_strjoin_gnl(new_cmd, replace_value);
	return (new_cmd);
}

// conv_en_var:
//	- $?
//	- save_this $var doesnt_save_this
// e.g: echo "test $t test"
// ***for env.c: export var name cant contain "?"
void	conv_env_var(char **cmd, char **envp, t_ms *ms)
{
	int		i;
	int		j;

	j = -1;
	i = -1;
	while (cmd[++i])
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '$' && !is_quote(cmd[i][j + 1])
				&& cmd[i][j + 1] != ' ' && cmd[i][j + 1])
				cmd[i] = replace(cmd[i], envp, ms);
		}
		j = -1;
	}
}
