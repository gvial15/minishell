/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:51:26 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 14:27:43 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_exit(t_ms *ms, t_cmd *cmd)
{
	int	nb_args;

	ms->err_last_child = 0;
	nb_args = 0;
	while (cmd->args[nb_args])
		nb_args++;
	if (nb_args > 1)
	{
		ms->err_last_child = 1;
		dup2(ms->std_fd[1], 1);
		printf("%s%s\n", cmd->args[0], ERR_BUILT_PDFRULES);
	}
	else if (ms->nb_cmd == 1)
		history_clear_n_exit(ms);
}
