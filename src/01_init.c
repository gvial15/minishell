/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/12 14:00:31 by mraymond         ###   ########.fr       */
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

static void	line_prompter_init(t_ms *ms)
{
	int		i;
	char	*path;

	ft_memset(ms->line_prompt, '\0', 200);
	ft_strlcpy(ms->line_prompt, PROMPTER_TITLE, ft_strlen(PROMPTER_TITLE) + 1);
	ms->line_path = &ms->line_prompt[ft_strlen(PROMPTER_TITLE)];
	i = 0;
	while (ms->envp[i] && ft_strncmp(ms->envp[i], "PWD=", 4) != 0)
		i++;
	ft_memset(ms->working_path, '\0', 1000);
	if (ms->envp[i])
	{
		path = &ms->envp[i][5];
		ft_strlcpy(ms->working_path, path, ft_strlen(path) + 1);
	}
	set_prompter_path(ms);
}

void	ms_init(t_ms *ms, char **envp)
{
	ms->envp = splitdup(envp);
	ms->cmds = NULL;
	ms->last_line = NULL;
	line_prompter_init(ms);
}

//put 1 in arg to erase;
t_ms	*get_ms(int erase)
{
	static t_ms	*ms = NULL;

	if (!ms)
		ms = (t_ms *)malloc(sizeof(t_ms));
	if (erase == 1)
		free(ms);
	return (ms);
}
