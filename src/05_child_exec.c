/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_child_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:36:55 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/07 11:00:57 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Execution of child command. CLear n exit if builtin or execve fail
*/
void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;
	int		fd_stdout;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	fd_stdout = pipe_redirection(ms, cmd);
	if (builtin_checker(cmd) == 1)
		builtin_exec(ms, cmd);
	else if (cmd->cmd_path)
	{
		execve(cmd->cmd_path, cmd->args, ms->envp);
		dup2(fd_stdout, 1);
		if (cmd->args)
			printf("%s%s%s\n", ERR_FIRST, ERR_EXECVE, cmd->args[0]);
		ms->err_last_child = 127;
	}
	closefd_ifopen(1);
	child_exit(ms);
}

// Set set stdin and stdout, make copy of stdout for error management
int	pipe_redirection(t_ms *ms, t_cmd *cmd)
{
	int	fd_stdout;

	fd_stdout = dup(1);
	dup2(cmd->fildes[0], 0);
	dup2(cmd->fildes[1], 1);
	close_all_cmd_fdin_fdout(ms);
	return (fd_stdout);
}

// if last cmd, keep err_last_child
// close and free and exit
void	child_exit(t_ms *ms)
{
	int	last_err;

	last_err = 0;
	if (ms->cmd_index == ms->nb_cmd - 1)
		last_err = ms->err_last_child;
	child_cleaning(ms);
	exit(last_err);
}

// Closing and free all
void	child_cleaning(t_ms *ms)
{
	close_all_cmd_fdin_fdout(ms);
	closefd_ifopen(0);
	closefd_ifopen(1);
	closefd_ifopen(ms->std_fd[0]);
	closefd_ifopen(ms->std_fd[1]);
	clear_history();
	ms_reset(ms);
	if (ms->envp)
		free_split(ms->envp);
	get_ms(1);
}
