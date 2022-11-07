/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:01:40 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/07 11:31:26 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*conv_env_var_here_doc(char *line, t_ms *ms)
{
	char	**split;
	char	*new_line;

	split = split_quotes(line);
	conv_env_var(split, ms, 1);
	new_line = split_to_str(split, 1);
	return (new_line);
}

// here doc loop inside child process for ctrl-d handling
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
	close(fd_pipe[1]);
	if (line)
		free(line);
	else
		exit(1);
	exit(0);
}

// create pipe and child for heredoc loop
int	here_doc(t_ms *ms, char *str_eof)
{
	int	fd_pipe[2];
	int	status;

	signal_init(sit_here_doc);
	pipe(fd_pipe);
	ms->here_doc_id = fork();
	if (ms->here_doc_id == 0)
		child_here_doc(str_eof, fd_pipe, ms);
	close(fd_pipe[1]);
	waitpid(0, &status, 0);
	signal_init(sit_exec);
	if (WEXITSTATUS(status) != 0)
	{
		close(fd_pipe[0]);
		return (-1);
	}
	return (fd_pipe[0]);
}
