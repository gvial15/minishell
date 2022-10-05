/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 10:05:01 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"




void	ms_init(t_ms *ms)
{
	signal(SIGINT, fct_sigint);
	signal(SIGQUIT, fct_sigquit);
	signal(SIGINT, fct_sigint);
	
	
}

