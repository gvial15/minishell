/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:32 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:27:34 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

// eg:
// input: <infile grep t > out | ...
// *cmd_path: /usr/bin/grep
// **args: "t"
// char *fd_in: infile ... int fd: open(infile, O_RDONLY)
// char *fd_out: out ... int fd: open(out, O_CREAT, O_RDWR)
typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	char			*fd_in;
	char			*fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
	char	*last_line;
	t_cmd	*cmds;
}	t_ms;

void	execute_cmds(t_ms *ms);
void	get_cmds(char **envp, t_ms *ms);
char	*get_cmd_path(char *cmd_brut, char **envp);
// lst
void	free_lst(t_cmd *head);
t_cmd	*lst_last(t_cmd *head);

#endif
