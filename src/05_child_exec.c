/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/07 18:39:47 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	pipe_redirection(ms);
	if (redirection_in(cmd) == 0)
	{
		redirection_out(cmd);
		execve(cmd->cmd_path, cmd->args, ms->envp);
		printf("%s%s%s\n", ERR_FIRST, ERR_EXECVE, cmd->args[0]);
	}
	exec_fail(ms);
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

void	pipe_redirection(t_ms *ms)
{
	dup2(ms->pipe[ms->cmd_index * 2], 0);
	dup2(ms->pipe[ms->cmd_index * 2 + 1], 1);
}

void	exec_fail(t_ms *ms)
{
	if (ms->cmd_index > 0)
	{
		close_keep_errno(ms->pipe[(ms->cmd_index * 2) - 1]);
		close_keep_errno(ms->pipe[(ms->cmd_index * 2)]);
		close_keep_errno(0);
	}
	if (ms->cmd_index < ms->nb_cmd - 1)
		close_keep_errno(1);
	free_ms(ms, 1);
	exit(errno);
}

void	close_keep_errno(int fd)
{
	int	temp_errno;

	temp_errno = errno;
	close(fd);
	errno = temp_errno;
}
