/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:28:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 10:43:30 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_init(t_ms *ms, int argc, char **argv, char **envp)
{
	char **temp;
	
	signal_init();
	ms->envp = envp;
	temp = argv;
	if (argc >= 2)
		printf("All argument are ignored. Show must go on!\n");
}

t_ms	*get_ms(void)
{
	static t_ms	*ms = NULL;

	if (!ms)
		ms = (t_ms *)malloc(sizeof(t_ms));
	return (ms);
}
