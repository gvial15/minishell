/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:48:08 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/21 13:00:06 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**export_(char *varname, char *varvalue, t_ms *ms)
{
	char	**args;
	char	**new_envp;

	args = ft_calloc(3, sizeof(char *));
	args[0] = ft_strdup("export");
	args[1] = ft_strjoin(varname, varvalue);
	args[2] = 0;
	new_envp = export_env_var(args, ms);
	free_split(args);
	return (new_envp);
}

static void	access_n_cd(t_ms *ms, t_cmd *cmd, char *newpath)
{
	char	path[1000];

	if (access(newpath, X_OK) == -1)
	{
		ms->err_last_child = 1;
		dup2(ms->std_fd[1], 1);
		if (access(newpath, F_OK) == -1)
			printf("%s%s%s%s%s\n", "ms: ", cmd->args[0], ": ", newpath,
				ERR_OPEN_NOSUCH);
		else
			printf("%s%s%s%s%s\n", "ms: ", cmd->args[0], ": ", newpath,
				ERR_OPEN_PERM);
	}
	else
	{
		ms->envp = export_("OLDPWD=", getcwd(path, 1000), ms);
		chdir(newpath);
		ms->envp = export_("PWD=", getcwd(path, 1000), ms);
	}
}

static void	cd_0arg(t_ms *ms, t_cmd *cmd)
{
	char	*homepath;
	int		i;

	i = 0;
	homepath = NULL;
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], "HOME=", 5))
		i++;
	if (ms->envp[i])
	{	
		homepath = &ms->envp[i][5];
		access_n_cd(ms, cmd, homepath);
	}
	else
		access_n_cd(ms, cmd, "/Users");
}

void	builtin_cd(t_ms *ms, t_cmd *cmd)
{	
	int	nb_args;

	ms->err_last_child = 0;
	nb_args = 0;
	while (cmd->args[nb_args])
		nb_args++;
	if (nb_args == 1)
		cd_0arg(ms, cmd);
	else
		access_n_cd(ms, cmd, cmd->args[1]);
}
