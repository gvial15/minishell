
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:03:18 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 12:47:50 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_echo(t_ms *ms, t_cmd *cmd)
{
	int	no_skipline;
	int	i;
	
	ms->err_last_child = 0;
	no_skipline = 0;
	i = 0;
	if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
	{
		no_skipline = 1;
		i += 1;
	}
	while (cmd->args[++i])
	{
		if (cmd->args[i + 1])
			printf("%s ", cmd->args[i]);
		else
			printf("%s", cmd->args[i]);
	}
	if (no_skipline == 0)
		printf("\n");
}
