#ifndef MS_H
# define MS_H

# include "libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_cmd
{							// $> <infile grep t > out | ...
	char			*cmd_path; // /usr/bin/grep
	char			**args; // "t"
	char			*fd_in; // open(infile, O_RDONLY)
	char			*fd_out; // open(out, O_CREAT, O_RDWR)
	struct s_cmd	*next;
} t_cmd; // linked list constructed in get_cmds.c, once done, passed to exec.c

typedef struct s_ms
{
	char	*last_line;
	t_cmd	*cmds;
} t_ms;

void	execute_cmds(t_ms *ms);
void	get_cmds(char **envp, t_ms *ms);
char	*get_cmd_path(char *cmd_brut, char **envp);
// lst
void	free_lst(t_cmd *head);
t_cmd	*lst_last(t_cmd *head);

#endif