/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/19 12:02:30 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;
	int		fd_stdout;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	fd_stdout = pipe_redirection(ms, cmd);
	if (builtin_checker(cmd) == 1)
		builtin_exec(ms, cmd);
	else
	{
		execve(cmd->cmd_path, cmd->args, ms->envp);
		printf("%s%s%s\n", ERR_FIRST, ERR_EXECVE, cmd->args[0]);
		ms->err_last_child = 127;
	}
	closefd_ifopen(1);
	dup2(fd_stdout, 1);
	child_exit(ms);
}

int	pipe_redirection(t_ms *ms, t_cmd *cmd)
{
	int	fd_stdout;

	fd_stdout = dup(1);
	dup2(cmd->fildes[0], 0);
	dup2(cmd->fildes[1], 1);
	close_all_cmd_fdin_fdout(ms);
	return (fd_stdout);
}

void	child_exit(t_ms *ms)
{
	close_all_cmd_fdin_fdout(ms);
	closefd_ifopen(0);
	closefd_ifopen(1);
	if (ms->cmd_index == ms->nb_cmd - 1)
	{
		ms_reset(ms);
		exit(ms->err_last_child);
	}
	ms_reset(ms);
	exit(0);
}
