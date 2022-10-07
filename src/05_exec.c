/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:01 by gvial             #+#    #+#             */
/*   Updated: 2022/10/07 16:28:13 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(t_ms *ms)
{
	ms->nb_cmd = ft_lstsize(ms->cmds);
	ms->child_id = (int *)ft_calloc(ms->nb_cmd, sizeof(int));
	fd_allocation(ms);
	child_creation(ms);
	waiting_n_closefd(ms);
}

void	child_creation(t_ms *ms)
{
	int	process_id;

	ms->cmd_index = -1;
	process_id = 1;
	while (++ms->cmd_index < ms->nb_cmd && process_id != 0)
	{
		process_id = fork();
		if (process_id != 0)
			ms->child_id[ms->cmd_index] = process_id;
	}
	if (process_id == 0)
		child_execution(ms);
}

int	child_process_to_index(t_ms *ms, int waitpid_return)
{
	int	i;

	i = 0;
	while (ms->child_id[i] && ms->child_id[i] != waitpid_return)
		i++;
	if (!ms->child_id[i])
		return (-1);
	return (i);
}

/* main process wait for each child to finish
Close both fd from precedent pipe
*/
void	waiting_n_closefd(t_ms *ms)
{
	int	i;
	int	child_id;
	int	status;
	int	child_index;

	i = -1;
	while (++i < ms->nb_cmd)
	{
		child_id = waitpid(0, &status, 0);
		if (child_id != -1)
		{
			child_index = child_process_to_index(ms, child_id);
			if (child_index > 0)
			{
				close_keep_errno(ms->pipe[(child_index * 2) - 1]);
				close_keep_errno(ms->pipe[(child_index * 2)]);
				if (WEXITSTATUS(status) != 0 && child_index < ms->nb_cmd - 1)
					close_keep_errno(ms->pipe[(child_index * 2) + 1]);
			}
		}
		else
			printf("ERROR EXITING CHILD PROCESS, NOT NORMAL\n");
	}
}

void	close_keep_errno(int fd)
{
	int	temp_errno;

	temp_errno = errno;
	close(fd);
	errno = temp_errno;
}

void	fd_allocation(t_ms *ms)
{
	int	i;
	int	temp_pipe[2];

	ms->pipe = (int *)malloc(sizeof(int) * ((ms->nb_cmd - 1) * 2 + 2));
	ms->pipe[0] = 0;
	ms->pipe[(ms->nb_cmd - 1) * 2 + 1] = 1;
	i = -1;
	while (++i < ms->nb_cmd)
	{
		pipe(temp_pipe);
		ms->pipe[i * 2 + 1] = temp_pipe[1];
		ms->pipe[i * 2 + 2] = temp_pipe[0];
	}
}

void	child_execution(t_ms *ms)
{
	t_cmd	*cmd;

	cmd = cmd_lst_index(ms, ms->cmd_index);
	pipe_redirection(ms, cmd);
	redirection_in(cmd);
	//redirection out
	//execution
	
}



void	pipe_redirection(t_ms *ms, t_cmd *cmd)
{
	dup2(ms->pipe[ms->cmd_index * 2], 0);
	dup2(ms->pipe[ms->cmd_index * 2 + 1], 1);
}

int	redirection_in(t_cmd *cmd)
{
	int	i;
	int	new_fd_in;

	i = -1;
	new_fd_in = 0;
	while (cmd->fd_in[++i] && new_fd_in != -1)
	{
		if (cmd->heredoc == 0)
			new_fd_in = here_doc(cmd->fd_in[i]);
		else
			new_fd_in = open_fd_in(cmd->fd_in[i]);
		if (new_fd_in != -1 && cmd->fd_in[i + 1])
			close(new_fd_in);
	}
	if (new_fd_in != -1)
		dup2(new_fd_in, 0);
}

int	open_fd_in(char *filename)
{
	int	new_fd_in;
	int	error;

	error = 0;
	if (access(filename, F_OK) == -1)
		error = openerr_nosuch;
	else if (access(filename, X_OK) == -1)
		error = openerr_perm;
	else
		new_fd_in = open(filename, O_RDONLY);
	return (print_open_err(filename, error));
}

int	print_open_err(char *filename, int error)
{
	if (error = 0)
		return (0);
	printf("%s%s", ERR_FIRST, filename);
	if (error = openerr_nosuch)
		printf("%s\n", ERR_OPEN_NOSUCH);
	else if (error == openerr_perm)
		printf("%s\n", ERR_OPEN_PERM);
	return (-1);
}

int	here_doc(char *str_eof)
{
	int		fd_pipe[2];
	char	*line;

	pipe(fd_pipe[2]);
	readline("> ");
	while (ft_strncmp(line, str_eof, ft_strlen(line)))
	{
		write(fd_pipe[1], line, ft_strlen(line));
		readline("> ");
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

t_cmd	*cmd_lst_index(t_ms *ms, int cmd_index)
{
	int		i;
	t_cmd	*temp;

	temp = ms->cmds;
	i = -1;
	while (++i < cmd_index && temp->next)
		temp = temp->next;
}
