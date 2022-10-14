/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:21:46 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/14 13:11:42 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

//close all pipe open (but not 0 and 1)
void	close_n_free_mspipe(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->pipe[++i])
	{
		if (ms->pipe[i] >= 3)
			close_keep_errno(ms->pipe[i]);
	}
	free(ms->pipe);
	ms->pipe = NULL;
}

void	close_keep_errno(int fd)
{
	int	temp_errno;

	temp_errno = errno;
	close(fd);
	errno = temp_errno;
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

/*if with_lstcmd = 1, call freelist on it too
*/
void	free_ms(t_ms *ms, int with_lstcmds)
{
	ms_reset(ms);
	
}
