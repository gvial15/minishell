/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:25:42 by mraymond          #+#    #+#             */
/*   Updated: 2022/07/19 12:45:42 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define NB_FD 100

typedef struct s_index
{
	size_t	fd;
	size_t	read;
	size_t	rtn;
	size_t	buf_loop;
	size_t	len_read;
}			t_index;

char	*get_next_line(int fd);
void	fd_findoralloc(int ptr_fd[NB_FD][BUFFER_SIZE + 2],
			int fd, t_index *s_i);
char	*rtn_calloc_n_cpy(char *str_rtn, t_index *s_i);
void	cpy_read_to_rtn(char *str_read, char *str_rtn, t_index *s_i,
			char *last_cpy);
char	*read_n_fill(char *str_read, char *str_rtn, t_index *s_i, int fd);

#endif
