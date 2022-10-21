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

static void	access_n_cd(t_ms *ms, t_cmd *cmd, char *newpath)
{
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
		chdir(newpath);
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
