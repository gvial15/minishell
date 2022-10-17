/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/17 10:24:33 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl-c -> SIGINT    ctrl-\ -> SIGQUIT    ctrl-d -> SIGABRT
void	signal_init(void)
{
	signal(SIGINT, fct_sigint);
	signal(SIGQUIT, fct_sigquit);
}

//ctrl-\ -> SIGQUIT
void	fct_sigquit(int sig)
{
	(void)sig;
}

//ctrl-c -> SIGINT
void	fct_sigint(int sig)
{
	t_ms	*ms;

	sig = 0;
	signal_init();
	ms = get_ms(0);
	if (ms->cmd_index >= ms->nb_cmd)
	{
		while (wait(0) != -1)
			wait(0);
		write(1, "\n", 1);
		if (ms->nb_cmd == 0)
		{
			ms_reset(ms);
			write(1, ms->line_prompt, ft_strlen(ms->line_prompt));
		}
	}
	else
		exec_fail(ms);
}
