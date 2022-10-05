/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:32 by gvial             #+#    #+#             */
/*   Updated: 2022/10/05 11:19:09 by mraymond         ###   ########.fr       */
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
}	t_ms;

//==============================================================================

//PROTOTYPES_FILES==============================================================
//0_main.c
void	prompter(t_ms *ms);

//01_init.c
void	ms_init(t_ms *ms, int argc, char **argv, char **envp);
t_ms	*get_ms(void);

//02_signal.c
void	signal_init(void);
void	fct_sigquit(int sig);
void	fct_sigint(int sig);
void	fct_sigabrt(int sig);

//exec.c 
//parse.c

//==============================================================================

#endif
