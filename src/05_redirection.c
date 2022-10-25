/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:29:35 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/25 11:02:25 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirection_in(t_ms *ms, t_cmd *cmd)
{
	int	i;
	int	new_fd_in;

	if (!cmd->fd_in)
		return (0);
	i = -1;
	new_fd_in = 0;
	while (cmd->fd_in[++i] && new_fd_in != -1)
	{
		if (cmd->heredoc[i] == 1)
			new_fd_in = here_doc(ms, cmd->fd_in[i]);
		else
			new_fd_in = open_fd_in(cmd->fd_in[i]);
		if (new_fd_in != -1 && cmd->fd_in[i + 1])
			close(new_fd_in);
	}
	return (new_fd_in);
}

int	open_fd_in(char *filename)
{
	int	error;

	error = 0;
	if (access(filename, F_OK) == -1)
		error = openerr_nosuch;
	else if (access(filename, R_OK) == -1)
		error = openerr_perm;
	else
		return (open(filename, O_RDONLY));
	return (print_open_err(filename, error));
}

int	print_open_err(char *filename, int error)
{
	if (error == 0)
		return (0);
	printf("%s%s", ERR_FIRST, filename);
	if (error == openerr_nosuch)
		printf("%s\n", ERR_OPEN_NOSUCH);
	else if (error == openerr_perm)
		printf("%s\n", ERR_OPEN_PERM);
	return (-1);
}

int	redirection_out(t_cmd *cmd)
{
	int	i;
	int	new_fd_out;

	if (!cmd->fd_out)
		return (0);
	i = -1;
	new_fd_out = 0;
	while (cmd->fd_out[++i] && new_fd_out != -1)
	{
		if (access(cmd->fd_out[i], F_OK) != -1
			&& access(cmd->fd_out[i], W_OK) == -1)
			new_fd_out = print_open_err(cmd->fd_out[i], openerr_perm);
		else if (cmd->append == 1)
			new_fd_out = open(cmd->fd_out[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			new_fd_out = open(cmd->fd_out[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (cmd->fd_out[i + 1] && new_fd_out != -1)
			close(new_fd_out);
	}
	return (new_fd_out);
}
