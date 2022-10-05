/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:58:59 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 10:04:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_init(void)
{
	signal(SIGINT, fct_sigint);
	signal(SIGQUIT, fct_sigquit);
	signal(SIGINT, fct_sigint);
}

void	fct_sigquit(int sig)
{
	t_ms	*ms;

	ms = get_ms();
	
}

void	fct_sigint(int sig)
{
	t_ms	*ms;

	ms = get_ms();
	
}