/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:37:15 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/07 17:43:08 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*if with_lstcmd = 1, call freelist on it too
*/
void	free_ms(t_ms *ms, int with_lstcmds)
{
	free(ms->last_line);
	free(ms->pipe);
	free(ms->child_id);
	if (with_lstcmds == 1)
		free_lst(ms->cmds);
}

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