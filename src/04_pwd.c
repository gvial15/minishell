/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:41:07 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 14:24:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_pwd(t_ms *ms, t_cmd *cmd)
{
	char	path[1000];

	ms->err_last_child = 0;
	if (cmd->args[1])
	{
		ms->err_last_child = 1;
		dup2(ms->std_fd[1], 1);
		printf("%s%s\n", cmd->args[0], ERR_BUILT_TOOMANYARGS);
	}
	else
		printf("%s\n", getcwd(path, 1000));
}
