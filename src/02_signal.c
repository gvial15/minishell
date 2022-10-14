/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/12 14:26:49 by mraymond         ###   ########.fr       */
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
void	fct_sigint(int sig2)
{
	t_ms	*ms;

	(void)sig2;
	ms = get_ms(0);
	if (ms->cmds && ms->cmd_index >= ms->nb_cmd)
		//loop to send kill in each child
	else
		//clear and exit process
}

