/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:37:15 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/14 13:09:15 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//option 0: with double ptr -- 1:only inside
void	free_dbl_ptr(void **ptr, int option)
{
	int	i;

	if (ptr)
	{
		i = -1;
		while (ptr[++i])
			free(ptr[i]);
		if (option == 0)
			free(ptr);
	}
}

void	close_all_cmd_fdin_fdout(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmds;
	while (cmd)
	{
		if (cmd->fildes[0] != -1)
		{
			close_keep_errno(cmd->fildes[0]);
			close_keep_errno(cmd->fildes[1]);
		}
		cmd = cmd->next;
	}
}

t_cmd	*lst_last(t_cmd *head)
{
	if (!head)
		return (head);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int	lst_len(t_cmd *head)
{
	int	len;

	if (!head)
		return (0);
	len = 1;
	while (head && head->next != NULL)
	{
		len++;
		head = head->next;
	}
	return (len);
}
