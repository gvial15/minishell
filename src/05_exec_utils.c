/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:21:46 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/07 11:07:28 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//close all ms->pipe open (except ms->pipe[0] and ms->pipe[last])
void	close_n_free_mspipe(t_ms *ms)
{
	int	i;

	i = 0;
	while (++i <= (ms->nb_cmd - 1) * 2)
		closefd_ifopen(ms->pipe[i]);
	free(ms->pipe);
	ms->pipe = NULL;
}

// check if fd open and keep errno if close return error
void	closefd_ifopen(int fd)
{
	struct stat	stat_buffer;
	int			temp_err;

	temp_err = errno;
	if (fstat(fd, &stat_buffer) != -1 && fd >= 3)
		close(fd);
	errno = temp_err;
}

//return the pointer of cmd accordingly of the index
t_cmd	*cmd_lst_index(t_ms *ms, int cmd_index)
{
	int		i;
	t_cmd	*temp;

	temp = ms->cmds;
	i = -1;
	while (++i < cmd_index && temp->next)
		temp = temp->next;
	return (temp);
}

// return index of a child process using table ms->child_id
int	child_process_to_index(t_ms *ms, int waitpid_return)
{
	int	i;

	i = 0;
	while (i < ms->nb_cmd && ms->child_id[i] != waitpid_return)
		i++;
	if (i == ms->nb_cmd)
		return (-1);
	return (i);
}

/* If terminal cursor x position is not 1, write \n
*/
void	if_xnot0_skipline(void)
{
	int				i;
	char			buf[100];
	struct termios	term;
	struct termios	restore;

	i = -1;
	while (++i < 100)
		buf[i] = 0;
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
	write(1, "\033[6n", 4);
	i = 0;
	while (buf[i++] != 'R')
		read(0, &buf[i], 1);
	tcsetattr(0, TCSANOW, &restore);
	if (buf[i - 3] != ';' || buf[i - 2] != '1' || buf[i - 1] != 'R')
		write(1, "\n", 1);
}
