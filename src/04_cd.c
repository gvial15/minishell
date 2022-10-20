/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:48:08 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 10:50:59 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	access_n_cd(t_ms *ms, t_cmd *cmd, char *newpath, int std_fd[2])
{
	if (access(newpath, X_OK) == -1)
	{
		ms->err_last_child = 1;
		dup2(std_fd[1], 1);
		if (access(newpath, F_OK) == -1)
			printf("%s%s%s%s\n", cmd->args[0], ERR_OPEN_NOSUCH, ": ", newpath);
		else
			printf("%s%s%s%s\n", cmd->args[0], ERR_OPEN_PERM, ": ", newpath);
	}
	else
		chdir(newpath);
}

static void	cd_2args(t_ms *ms, t_cmd *cmd, int std_fd[2])
{
	char	pwdbuf[1000];
	char	*wheretochange;
	char	*pwdend;
	char	newpath[1000];

	ft_memset(newpath, '\0', 1000);
	getcwd(pwdbuf, 1000);
	wheretochange = ft_strnstr(pwdbuf, cmd->args[1], 1000);
	if (!wheretochange)
	{
		ms->err_last_child = 1;
		printf("%s%s%s\n", cmd->args[0], ERR_BUILT_NOTINPWD, cmd->args[1]);
	}
	else
	{
		pwdend = &wheretochange[ft_strlen(cmd->args[1])];
		wheretochange[0] = '\0';
		ft_strlcat(newpath, pwdbuf, 1000);
		ft_strlcat(newpath, cmd->args[2], 1000);
		ft_strlcat(newpath, pwdend, 1000);
		access_n_cd(ms, cmd, newpath, std_fd);
	}
}

static void	cd_0arg(t_ms *ms, t_cmd *cmd, int std_fd[2])
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
		access_n_cd(ms, cmd, homepath, std_fd);
	}
	else
		access_n_cd(ms, cmd, "/Users", std_fd);
}

void	builtin_cd(t_ms *ms, t_cmd *cmd, int std_fd[2])
{	
	int	nb_args;

	ms->err_last_child = 0;
	nb_args = 0;
	while (cmd->args[nb_args])
		nb_args++;
	if (nb_args > 3)
	{
		ms->err_last_child = 1;
		dup2(std_fd[1], 1);
		printf("%s%s\n", cmd->args[0], ERR_BUILT_TOOMANYARGS);
	}
	else if (nb_args == 3)
		cd_2args(ms, cmd, std_fd);
	else if (nb_args == 1)
		cd_0arg(ms, cmd, std_fd);
	else
		access_n_cd(ms, cmd, cmd->args[1], std_fd);
}

