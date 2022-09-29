/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:46 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:27:48 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ms.h"

void	print_cmd_lst(t_cmd *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("*****\n");
		printf("cmd#%i\n", i);
		printf("cmd_path: %s\n", head->cmd_path);
		printf("fd_in: %s\n", head->fd_in);
		printf("fd_out: %s\n", head->fd_out);
		head = head->next;
		i++;
	}
}
/************^^^^^testing functions^^^^^************/

static void	init_ms(t_ms *ms)
{
	ms->cmds = NULL;
	ms->last_line = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	if (ac != 1)
		return (0);
	init_ms(&ms);
	while (1)
	{
		ms.last_line = readline("$> ");
		if (!ft_strncmp(ms.last_line, "exit", 4))
			exit(0);
		if (ms.last_line)
		{
			get_cmds(envp, &ms);
			print_cmd_lst(ms.cmds);
			execute_cmds(&ms);
			free_lst(ms.cmds);
			ms.cmds = NULL;
		}
	}
}

// parsing stdin/out for each cmds is working test:
// <from >to | <from2 >to2 ..

// note
// ➜  ms <test grept a | <test grep a
// zsh: command not found: grept
// a
