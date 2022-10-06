/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:32 by gvial             #+#    #+#             */
/*   Updated: 2022/10/06 10:39:04 by mraymond         ###   ########.fr       */
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
# define PROMPTER_TITLE " ms->"
# define PROMPTER_END " $> "

# define ERR_FIRST "minishell: "

//line error
# define ERR_LINE_QUOTE "line parse error -> open quote"
# define ERR_LINE_PIPE "syntax error near unexpected token `|'"

//==============================================================================

//STRUCTS=======================================================================

typedef struct s_cmd
{
	char			*cmd_path;
	char			**args;
	char			*fd_in;
	char			**fd_out;
	int				append_out;
	struct s_cmd	*next;
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
int		have_sign(char *s);
void	free_lst(t_cmd *head);
t_cmd	*lst_last(t_cmd *head);
int		find_cmd_i(char **split);
void	parse(char **envp, t_ms **ms);
char	*get_cmd_path(char *cmd, char **envp);
char	*get_cmd_path(char *cmd_brut, char **envp);

//04_builtins
char	**add_env_var(char **envp, char *var_name);

//05_exec.c
void	exec(t_ms **ms);

//line_parcing
int		valid_line(char *line);

// utils

//==============================================================================

#endif
