/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/12 11:11:45 by mraymond         ###   ########.fr       */
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

t_cmd	*cmd_lst_index(t_ms *ms, int cmd_index)
{
	int		i;
	t_cmd	*temp;

	temp = ms->cmds;
	i = -1;
	while (++i < cmd_index && temp->next)
		temp = temp->next;
	return (temp);
}

void	closing_pipe(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmds;
	while (cmd)
	{
		close_keep_errno(cmd->fildes[0]);
		close_keep_errno(cmd->fildes[1]);
		cmd = cmd->next;
	}
}

int	pipe_redirection(t_ms *ms, t_cmd *cmd)
{
	int	fd_stdout;

	fd_stdout = dup(1);
	dup2(cmd->fildes[0], 0);
	dup2(cmd->fildes[1], 1);
	closing_pipe(ms);
	return (fd_stdout);
}

void	exec_fail(t_ms *ms, t_cmd *cmd)
{
	if (cmd->fildes[0] != 0)
		close_keep_errno(cmd->fildes[0]);
	if (cmd->fildes[1] != 1)
		close_keep_errno(cmd->fildes[1]);
	free_ms(ms, 1);
	exit(ms->child_id[ms->cmd_index]);
}

void	close_keep_errno(int fd)
{
	int	temp_errno;

	temp_errno = errno;
	close(fd);
	errno = temp_errno;
}
