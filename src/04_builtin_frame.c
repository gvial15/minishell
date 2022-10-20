/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_builtin_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:57:42 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/20 14:20:34 by mraymond         ###   ########.fr       */
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

static void	builtin_redirection(t_ms *ms, t_cmd *cmd, int in_out)
{
	if (in_out == 0)
	{
		dup2(cmd->fildes[0], 0);
		dup2(cmd->fildes[1], 1);
	}
	else
	{
		dup2(ms->std_fd[0], 0);
		dup2(ms->std_fd[1], 1);
	}
}

void	builtin_exec(t_ms *ms, t_cmd *cmd)
{
	builtin_redirection(ms, cmd, 0);
	if (ft_strncmp(cmd->args[0], "echo", ft_strlen("echo") + 1) == 0)
		builtin_echo(ms, cmd);
	else if (ft_strncmp(cmd->args[0], "cd", ft_strlen("cd") + 1) == 0)
		builtin_cd(ms, cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", ft_strlen("pwd") + 1) == 0)
		builtin_pwd(ms, cmd);
	else if (ft_strncmp(cmd->args[0], "export", ft_strlen("export") + 1) == 0)
		ms->envp = export_env_var(ms->envp, cmd->args, ms);
	else if (ft_strncmp(cmd->args[0], "unset", ft_strlen("unset") + 1) == 0)
		ms->envp = unset_env_var(ms->envp, cmd->args, ms);
	else if (ft_strncmp(cmd->args[0], "env", ft_strlen("env") + 1) == 0)
		printf("call builtin function %s\n", cmd->args[0]);
	else if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit") + 1) == 0)
		builtin_exit(ms, cmd);
	builtin_redirection(ms, cmd, 1);
}
