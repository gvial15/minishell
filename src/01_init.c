/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/17 09:52:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_prompter_path(t_ms *ms)
{
	int	i_last_dir;

	i_last_dir = ft_strrchr_i(ms->working_path, '/') + 1;
	ft_strlcpy(ms->line_path, &ms->working_path[i_last_dir],
		ft_strlen(&ms->working_path[i_last_dir]) + 1);
	ft_strlcpy(&ms->line_path[ft_strlen(&ms->working_path[i_last_dir])],
		PROMPTER_END, ft_strlen(PROMPTER_END) + 1);
}

//if init_workpath = 1, take the pwd working_path
void	fill_line_prompter(t_ms *ms, int init_workingpath)
{
	int		i;
	char	*path;

	path = NULL;
	ft_memset(ms->line_prompt, '\0', 200);
	ft_strlcpy(ms->line_prompt, PROMPTER_TITLE, ft_strlen(PROMPTER_TITLE) + 1);
	ms->line_path = &ms->line_prompt[ft_strlen(PROMPTER_TITLE)];
	if (init_workingpath == 1 || ft_strrchr_i(ms->working_path, '/') == -1)
	{
		i = 0;
		while (ms->envp[i] && ft_strncmp(ms->envp[i], "PWD=", 4) != 0)
			i++;
		ft_memset(ms->working_path, '\0', 1000);
		if (ms->envp[i])
			path = &ms->envp[i][5];
	}
	else
		path = &ms->working_path[ft_strrchr_i(ms->working_path, '/') + 1];
	ft_strlcpy(ms->working_path, path, ft_strlen(path) + 1);

	set_prompter_path(ms);
}

void	ms_init(t_ms *ms, char **envp)
{
	ms->envp = envp;
	ms->cmds = NULL;
	ms->last_line = NULL;
	ms->line_path = NULL;
	ms->pipe = NULL;
	ms->cmds = NULL;
	ms->cmd_index = 0;
	ms->nb_cmd = 0;
	fill_line_prompter(ms, 1);
	signal_init();
}

void	ms_reset(t_ms *ms)
{
	if (ms->last_line)
		free(ms->last_line);
	ms->last_line = NULL;
	if (ms->cmds)
		free_cmds(ms);
	if (ms->pipe)
		close_n_free_mspipe(ms);
	fill_line_prompter(ms, 0);
	ms->cmds = NULL;
	ms->cmd_index = 0;
	ms->nb_cmd = 0;
}

//put 1 in arg to erase;
t_ms	*get_ms(int erase)
{
	static t_ms	*ms = NULL;

	if (!ms)
		ms = (t_ms *)malloc(sizeof(t_ms));
	if (erase == 1)
	{
		free(ms);
		ms = NULL;
	}
	return (ms);
}
