/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:01 by gvial             #+#    #+#             */
/*   Updated: 2022/10/07 15:14:52 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(t_ms *ms)
{
	ms->nb_cmd = ft_lstsize(ms->cmds);
	ms->child_id = (int *)ft_calloc(ms->nb_cmd, sizeof(int));
	fd_allocation(ms);
	child_creation(ms);
	waiting_n_closefd(ms);
}

void	child_creation(t_ms *ms)
{
	int	process_id;

	ms->cmd_index = -1;
	process_id = 1;
	while (++ms->cmd_index < ms->nb_cmd && process_id != 0)
	{
		process_id = fork();
		if (process_id != 0)
			ms->child_id[ms->cmd_index] = process_id;
	}
	if (process_id == 0)
		child_execution(ms);
}

int	child_process_to_index(t_ms *ms, int waitpid_return)
{
	int	i;

	i = 0;
	while (ms->child_id[i] && ms->child_id[i] != waitpid_return)
		i++;
	if (!ms->child_id[i])
		return (-1);
	return (i);
}

/* main process wait for each child to finish
Close both fd from precedent pipe
*/
void	waiting_n_closefd(t_ms *ms)
{
	int	i;
	int	child_id;
	int	status;
	int	child_index;

	i = -1;
	while (++i < ms->nb_cmd)
	{
		child_id = waitpid(0, &status, 0);
		if (child_id != -1)
		{
			child_index = child_process_to_index(ms, child_id);
			if (child_index > 0)
			{
				close_keep_errno(ms->pipe[(child_index * 2) - 1]);
				close_keep_errno(ms->pipe[(child_index * 2)]);
				if (WEXITSTATUS(status) != 0 && child_index < ms->nb_cmd - 1)
					close_keep_errno(ms->pipe[(child_index * 2) + 1]);
			}
		}
		else
			printf("ERROR EXITING CHILD PROCESS, NOT NORMAL\n");
	}
}

void	close_keep_errno(int fd)
{
	int	temp_errno;

	temp_errno = errno;
	close(fd);
	errno = temp_errno;
}

void	fd_allocation(t_ms *ms)
{
	int	i;
	int	temp_pipe[2];

	ms->pipe = (int *)malloc(sizeof(int) * ((ms->nb_cmd - 1) * 2 + 2));
	ms->pipe[0] = 0;
	ms->pipe[(ms->nb_cmd - 1) * 2 + 1] = 1;
	i = -1;
	while (++i < ms->nb_cmd)
	{
		pipe(temp_pipe);
		ms->pipe[i * 2 + 1] = temp_pipe[1];
		ms->pipe[i * 2 + 2] = temp_pipe[0];
	}
}

void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	pipe_redirection(ms, cmd);
	//redirection in
	//redirection out
	//execution
	
}

void	pipe_redirection(t_ms *ms, t_cmd *cmd)
{
	dup2(ms->pipe[ms->cmd_index * 2], 0);
	dup2(ms->pipe[ms->cmd_index * 2 + 1], 1);
}



t_cmd	*cmd_lst_index(t_ms *ms, int cmd_index)
{
	int		i;
	t_cmd	*temp;

	temp = ms->cmds;
	i = -1;
	while (++i < cmd_index && temp->next)
		temp = temp->next;
}
