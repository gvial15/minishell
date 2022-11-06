/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:01:40 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/03 15:08:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// repair
static char	*conv_env_var_here_doc(char *line, t_ms *ms)
{
	char	**split;
	char	*new_line;

	split = split_quotes(line);
	conv_env_var(split, ms, 1);
	new_line = split_to_str(split, 1);
	return (new_line);
}

static int	child_here_doc(char *str_eof, int fd_pipe[2], t_ms *ms)
{
	char	*line;

	close(fd_pipe[0]);
	line = readline("> ");
	while (line && ft_strncmp(line, str_eof, ft_strlen(line) + 1))
	{
		if (ft_strnstr(line, "$", ft_strlen(line)))
			line = conv_env_var_here_doc(line, ms);
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd_pipe[1]);
	exit(0);
}

int	here_doc(t_ms *ms, char *str_eof)
{
	int		fd_pipe[2];

	signal_init(sit_here_doc);
	pipe(fd_pipe);
	ms->here_doc_id = fork();
	if (ms->here_doc_id == 0)
		child_here_doc(str_eof, fd_pipe, ms);
	close(fd_pipe[1]);
	wait(0);
	signal_init(sit_exec);
	if (ms->err_last_child == 1)
	{
		close(fd_pipe[0]);
		return (-1);
	}
	return (fd_pipe[0]);
}
