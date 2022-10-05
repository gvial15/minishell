/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:32 by gvial             #+#    #+#             */
/*   Updated: 2022/10/05 09:20:26 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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
	char	**envp;
	t_cmd	*cmds;
}	t_ms;

void	exec(t_ms *ms);
void	get_cmds(char **envp, t_ms *ms);
char	*get_cmd_path(char *cmd_brut, char **envp);
char	**add_env_var(char **envp, char *var_name);
char	**unset_env_var(char **envp, char *var_name);

// utils
int		have_sign(char *s);
void	free_lst(t_cmd *head);
t_cmd	*lst_last(t_cmd *head);
int		find_cmd_i(char **split);

#endif
