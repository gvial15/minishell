
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

//return 0 if flag and 1 if not
static int	is_flag_n(char *arg)
{
	int	i;
	int	val_line;
	
	val_line = 1;
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		i = 1;
		val_line = 0;
		while (arg[++i] && val_line == 0)
		{
			if (arg[i] != 'n')
				val_line = 1;
		}
	}
	return (val_line);
}

void	builtin_echo(t_ms *ms, t_cmd *cmd)
{
	int	no_skipline;
	int	i;
	
	ms->err_last_child = 0;
	no_skipline = 0;
	i = 1;
	while (is_flag_n(cmd->args[i]) != 1)
		i++;
	if (i > 1)
		no_skipline = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i + 1])
			printf("%s ", cmd->args[i]);
		else
			printf("%s", cmd->args[i]);
		i++;
	}
	if (no_skipline == 0)
		printf("\n");
}

