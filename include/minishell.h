/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:32 by gvial             #+#    #+#             */
/*   Updated: 2022/10/12 13:27:27 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//LIBRARIES=====================================================================
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

//==============================================================================

# ifndef DEBUG
#  define DEBUG 0
# endif

//MESSAGES=====================================================================

//prompter
# define PROMPTER_TITLE " ms-> "
# define PROMPTER_END " $> "

# define ERR_FIRST "minishell: "

//parsing
# define GREATER_THAN ">>"
# define LESSER_THAN "<<"

//line error
# define ERR_LINE_QUOTE "line parse error -> open quote"
# define ERR_LINE_NOCMD "line parse error -> no command"
# define ERR_SYNTAX_ERROR "syntax error near unexpected token "
# define ERR_LINE_PIPE "`|'"
# define ERR_LINE_4IN "`<'"
# define ERR_LINE_5IN "`<<'"
# define ERR_LINE_3OUT "`>'"
# define ERR_LINE_4OUT "`>>'"
# define ERR_LINE_NEWLINE "`newline'"

//open_err
# define ERR_OPEN_NOSUCH ": No such file or directory"
# define ERR_OPEN_PERM ": Permission denied"

# define ERR_EXECVE "command not found: "

//==============================================================================

//ENUM_ERROR====================================================================

enum e_line_err
{
	lineerr_quote = 1,
	lineerr_nocmd,
	lineerr_pipe,
	lineerr_3in,
	lineerr_4in,
	lineerr_3out,
	lineerr_4out
};

enum e_open_err
{
	openerr_nosuch,
	openerr_perm
};

//==============================================================================

//STRUCTS=======================================================================

typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	char			**fd_in;
	char			**fd_out;
	int				append;
	int				*heredoc;
	struct s_cmd	*next;
	int				fildes[2];
}	t_cmd;

typedef struct s_ms
{
	char	*last_line;
	char	**envp;
	int		*pipe;
	t_cmd	*cmds;
	char	line_prompt[200];
	char	*line_path;
	char	working_path[1000];
	int		cmd_index;
	int		nb_cmd;
	int		*child_id;
	int		err_num;
}	t_ms;

//==============================================================================

//PROTOTYPES_FILES==============================================================
//0_main.c

//01_init.c
void	set_prompter_path(t_ms *ms);
void	ms_init(t_ms *ms, char **envp);
t_ms	*get_ms(void);

//02_signal.c
void	signal_init(void);
void	fct_sigquit(int sig);
void	fct_sigint(int sig);
void	fct_sigabrt(int sig);

//03_parsing
int		have_redirec(char *s);
int		have_dbl_redirec(char *s);
void	free_cmds(t_cmd *head);
t_cmd	*lst_last(t_cmd *head);
int		find_cmd_i(char **split);
void	parse(char **envp, t_ms *ms);
char	*isolate_cmd(char *cmd_brut);
char	*get_cmd_path(char *cmd, char **envp);
char	**get_fd_in_out(t_cmd *new_cmd, char *cmd, char sign);
char	*space_out_redirections(char *last_line);

//04_builtins
char	**add_env_var(char **envp, char **vars);

//01_valid_line
int		valid_line(char *line);
int		print_line_err(int error);

// utils
int		lst_len(t_cmd *head);

//utils2
void	free_dbl_ptr(void **ptr, int option);

//EXECUTION---------------------------------------------------------------------
//05_exec.c
void	exec(t_ms *ms);
void	fd_allocation(t_ms *ms);
void	fd_redirection(t_ms *ms);
void	child_creation(t_ms *ms);
void	waiting_n_closefd(t_ms *ms);

//05_child_exec.c
void	child_execution(t_ms *ms);
void	closing_pipe(t_ms *ms);
int		pipe_redirection(t_ms *ms, t_cmd *cmd);
void	exec_fail(t_ms *ms, t_cmd *cmd);

//05_redirection.c
int		redirection_in(t_cmd *cmd);
int		here_doc(char *str_eof);
int		open_fd_in(char *filename);
int		print_open_err(char *filename, int error);
int		redirection_out(t_cmd *cmd);

//05_exec_utils.c
int		child_process_to_index(t_ms *ms, int waitpid_return);
void	close_ms_pipe(t_ms *ms);
void	close_keep_errno(int fd);
t_cmd	*cmd_lst_index(t_ms *ms, int cmd_index);
void	free_ms(t_ms *ms, int with_lstcmds);

//==============================================================================

#endif
