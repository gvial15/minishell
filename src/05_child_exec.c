/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/17 08:57:50 by mraymond         ###   ########.fr       */
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
	exec_fail(ms, cmd);
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

void	exec_fail(t_ms *ms, t_cmd *cmd)
{
	close_keep_errno(cmd->fildes[0]);
	close_keep_errno(cmd->fildes[1]);
	ms_reset(ms);
	exit(0);
}

