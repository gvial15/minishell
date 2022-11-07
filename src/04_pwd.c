/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:41:07 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/07 10:54:11 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//print pwd except if flag used
void	builtin_pwd(t_ms *ms, t_cmd *cmd)
{
	char	path[1000];

	ms->err_last_child = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1] != '\0')
	{
		ms->err_last_child = 1;
		dup2(ms->std_fd[1], 1);
		printf("%s%s%s\n", cmd->args[0], ": usage", ERR_BUILT_PDFRULES);
	}
	else
		printf("%s\n", getcwd(path, 1000));
}
