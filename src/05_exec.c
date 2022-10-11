/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:01 by gvial             #+#    #+#             */
/*   Updated: 2022/10/11 09:30:58 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(t_ms *ms)
{
	ms->nb_cmd = lst_len(ms->cmds);
	ms->child_id = (int *)ft_calloc(ms->nb_cmd, sizeof(int));
	fd_allocation(ms);
	child_creation(ms);
	waiting_n_closefd(ms);
}

void	fd_allocation(t_ms *ms)
{
	int	i;
	int	temp_pipe[2];

	ms->pipe = (int *)malloc(sizeof(int) * ((ms->nb_cmd - 1) * 2 + 2));
	ms->pipe[0] = 0;
	ms->pipe[(ms->nb_cmd - 1) * 2 + 1] = 1;
	i = -1;
	while (++i < ms->nb_cmd - 1)
	{
		pipe(temp_pipe);
		ms->pipe[i * 2 + 1] = temp_pipe[1];
		ms->pipe[i * 2 + 2] = temp_pipe[0];
	}
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
			}
			if (child_index == ms->nb_cmd - 1)
				ms->err_num = 0;
		}
		//read in pipe_err
	}
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