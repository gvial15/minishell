/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 10:24:51 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl-c -> SIGINT ctrl-d -> SIGQUIT ctrl-\ -> SIGABRT
void	signal_init(void)
{
	signal(SIGINT, fct_sigint);
	signal(SIGQUIT, fct_sigquit);
	signal(SIGABRT, fct_sigabrt);
}

void	fct_sigquit(int sig)
{
	t_ms	*ms;

	ms = get_ms();


	//TEMP-----------------------------------
	printf("signal ctrl-d -> free main/child process and exit minishell");
	exit(0);
}

void	fct_sigint(int sig)
{
	t_ms	*ms;

	ms = get_ms();
	
	//TEMP-----------------------------------
	printf("signal ctrl-c -> child:free and exit / main restart to prompter");

}

void	fct_sigabrt(int sig)
{
	//TEMP-----------------------------------
	printf("signal ctrl-\\ -> do nothing");
}
