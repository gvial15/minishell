/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:33:33 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 10:33:33 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = get_ms();
	ms_init(ms, argc, argv, envp);
	while (1)
	{
		prompter(ms);
	}
	return (0);
}

void	prompter(t_ms *ms)
{
	ms->last_line = readline(" >> ");
	add_history(ms->last_line);
}
