/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:33:33 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 11:15:48 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	int		temp_loop = 10;

	ms = get_ms();
	ms_init(ms, argc, argv, envp);
	while (--temp_loop > 0)
	{
		prompter(ms);
	}
	return (0);
}

void	prompter(t_ms *ms)
{
	ms->last_line = readline(" minishell >> ");
	while (ms->last_line && ft_strlen(ms->last_line) == 0)
		ms->last_line = readline(" >> ");
	add_history(ms->last_line);
}
