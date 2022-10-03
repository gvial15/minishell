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
		printf("args:\n");
		print_split(head->args);
		printf("fd_in: %s\n", head->fd_in);
		printf("fd_out: %s\n", head->fd_out);
		head = head->next;
		i++;
	}
}
/************^^^^^testing functions^^^^^************/

static void	init_ms(t_ms *ms, char **envp)
{
	int		i;

	ms->cmds = NULL;
	ms->last_line = NULL;
	i = 0;
	while (envp[i])
		i++;
	ms->envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		ms->envp[i] = ft_strdup(envp[i]);
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	if (ac != 1)
		return (0);
	init_ms(&ms, envp);
	while (1)
	{
		ms.last_line = readline("$> ");
		if (ms.last_line)
		{
			add_history(ms.last_line);
			get_cmds(envp, &ms);
			print_cmd_lst(ms.cmds);
			exec(&ms);
			print_split(ms.envp);
			free_lst(ms.cmds);
			ms.cmds = NULL;
		}
	}
	free_split(ms.envp);
}

// (1) this version parses each pipe in a linked lst and then execute the linked lst
// (2) another way could be to parse + execute them one by one, just start at the exec step directly and
// (2) .. use the parsing cmds to get needed info directly inside the exec.c functs.)
// (2) .. then save the fd_in/fd_out state in a t_state struct for the next execution
//
// my plan (1):
//
//  eg. -> <infile cmd args > out | <infile2 cmd2 args > out2
//					|							|
//					|							|
//					|---------------------------|
//					|
//					|
// 	parse all the "pipe" into a linked list (t_cmd)
//	eg:
//  {
//		cmd_path: usr/bin/cmd;
//		args: {"args", 0};
//		fd_in: infile;
//		fd_out: out;
//	}
//	
//	then send linked list to exec() that will execute them one by one
//	redirecting stdin/stdout accordingly each time
