/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/04 09:59:47 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl-c -> SIGINT    ctrl-\ -> SIGQUIT    ctrl-d -> SIGABRT
void	signal_init(int situation)
{
	signal(SIGQUIT, fct_sigquit);
	if (situation == 0)
		signal(SIGINT, fct_sigint_prompter);
	else if (situation == 1)
		signal(SIGINT, fct_sigint);
	else if (situation == 2)
		signal(SIGINT, fct_sigint_here_doc);
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

	(void) sig;
	ms = get_ms(0);
	signal_init(sit_exec);
	ms->signal = sig;
	ms->err_last_child = 130;
	if (ms->cmd_index < ms->nb_cmd && ms)
		child_exit(ms);
}

void	fct_sigint_prompter(int sig)
{
	t_ms	*ms;

	(void) sig;
	ms = get_ms(0);
	signal_init(sit_prompter);
	ms->signal = sig;
	ms->err_last_child = 1;
	ms_reset(ms);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	fct_sigint_here_doc(int sig)
{
	t_ms	*ms;

	(void) sig;
	ms = get_ms(0);
	signal_init(sit_here_doc);
	ms->signal = sig;
	ms->err_last_child = 1;
	if (ms->here_doc_id == 0)
		child_exit(ms);
	else
		write(1, "\n", 1);
}

