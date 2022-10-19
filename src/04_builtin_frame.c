/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_builtin_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:57:42 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/19 10:54:31 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_program_path(t_ms *ms, char *arg0)
{
	getcwd(ms->program_path, 1000);
	ft_strlcat(ms->program_path, "/", 1000);
	arg0[ft_strrchr_i(arg0, '/') + 1] = '\0';
	ft_strlcat(ms->program_path, arg0, 1000);
}


int	builtin_checker(t_ms *ms, int cmd_index)
{
	t_cmd	*cmd;
	char	*path_name;
	char	*filename;

	cmd = cmd_lst_index(ms, cmd_index);
	path_name = ft_strjoin("")
}
