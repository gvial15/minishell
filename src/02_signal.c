/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/17 14:39:04 by mraymond         ###   ########.fr       */
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
	(void) sig;
	t_ms	*ms;

	sig = 0;
	ms = get_ms(0);
	signal_init();
	if (ms->nb_cmd == 0)
	{
		if (ms->nb_cmd == 0)
			ms_reset(ms);
		write(1, " \n", 2);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (ms->cmd_index < ms->nb_cmd)
		exec_fail(ms);
}

/*
void	set_attribute(t_ms *ms)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->saved);
	ms->attributes = ms->saved;
	ms->attributes.c_lflag &= ~ECHO;
	//ms->attributes.c_lflag ^= ECHO;
	//tcsetattr(STDIN_FILENO, TCSANOW, &ms->attributes);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ms->attributes);
}
*/