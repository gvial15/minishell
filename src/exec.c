/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:01 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:03 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

// receive the t_cmd *cmds linked list and excecute them one by one
// redirecting stdin/out accordingly for each commands
void	exec(t_ms *ms)
{
	t_cmd	*current;

	current = ms->cmds;
	while (current)
	{
		if (!ft_strnstr(current->cmd_path, "export", ft_strlen(current->cmd_path)))
		{
			// execute cmd
		}
		current = current->next;
	}
}
