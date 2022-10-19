/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_builtin_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:57:42 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/19 12:21:41 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//check if its a builtin
int	builtin_checker(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo") + 1) == 0
		|| ft_strncmp(cmd->args[0], "cd", ft_strlen("cd") + 1) == 0
		|| ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd") + 1) == 0
		|| ft_strncmp(cmd->args[0], "export", ft_strlen("export") + 1) == 0
		|| ft_strncmp(cmd->args[0], "unset", ft_strlen("unset") + 1) == 0
		|| ft_strncmp(cmd->args[0], "env", ft_strlen("env") + 1) == 0
		|| ft_strncmp(cmd->args[0], "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	return (0);
}

void	builtin_exec(t_ms *ms, t_cmd *cmd)
{
	(void) ms;
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen("cd") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen("export") + 1) == 0)
		ms->envp = export_env_var(ms->envp, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen("unset") + 1) == 0)
		ms->envp = unset_env_var(ms->envp, cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen("env") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else
		printf("Oups, pensait que c'etait un builtin mais pas exec");
}
