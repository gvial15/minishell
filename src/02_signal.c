/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 11:10:22 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl-c -> SIGINT    ctrl-\ -> SIGQUIT    ctrl-d -> SIGABRT
void	signal_init(void)
{
	signal(SIGINT, fct_sigint);
	signal(SIGQUIT, fct_sigquit);
	signal(SIGTERM, fct_sigabrt);
}

//ctrl-\ -> SIGQUIT
void	fct_sigquit(int sig)
{
	t_ms	*ms;
	int		temp;

	temp = sig;
	ms = get_ms();

	//TEMP-----------------------------------
	//printf("SIGQUIT\n");
	//printf("SIGQUIT ctrl-\\ -> do nothing\n");
}

//ctrl-c -> SIGINT
void	fct_sigint(int sig2)
{
	t_ms	*ms;
	int		temp;

	temp = sig2;
	ms = get_ms();
	
	//TEMP-----------------------------------
	printf("SIGINT\n");
	//printf("signal int -> child:free and exit / main restart to prompter\n");
	//TEMP-----------------------------------
	//printf("signal ctrl-\\ -> do nothing\n");

}

//ctrl-d -> ???????
void	fct_sigabrt(int sig3)
{
	int		temp;

	temp = sig3;
	//TEMP-----------------------------------
	printf("SIGABRT\n");
	//printf("signal ctrl-c -> child:free and exit / main restart to prompter\n");
}
