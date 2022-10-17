/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/17 09:42:45 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;
	int		fd_stdout;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	fd_stdout = pipe_redirection(ms, cmd);
	execve(cmd->cmd_path, cmd->args, ms->envp);
	dup2(fd_stdout, 1);
	printf("%s%s%s\n", ERR_FIRST, ERR_EXECVE, cmd->args[0]);
	exec_fail(ms);
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

void	exec_fail(t_ms *ms)
{
	close_all_cmd_fdin_fdout(ms);
	close(0);
	close(1);
	ms_reset(ms);
	//if (ms->cmd_index == ms->nb_cmd - 1)
		//pipe_err
	exit(0);
}
