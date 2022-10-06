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

#include "../include/minishell.h"

void	print_cmd_lst(t_cmd *head)
{
	int	i;

	if (!DEBUG)
		return ;
	i = 0;
	while (head)
	{
		printf("*****\n");
		printf("cmd#%i\n", i);
		printf("cmd_path: %s\n", head->cmd_path);
		printf("args:\n");
		print_split(head->args);
		printf("fd_in: %s\n", head->fd_in);
		printf("fd_out: \n");
		print_split(head->fd_out);
		printf("append:%i\n", head->append);
		head = head->next;
		i++;
	}
}
/************^^^^^testing functions^^^^^************/

static void	prompter(t_ms *ms)
{
	ms->last_line = readline(" minishell >> ");
	while (ms->last_line && ft_strlen(ms->last_line) == 0)
		ms->last_line = readline(" minishell >> ");
	if (ft_strnstr(ms->last_line, "exit", 4))
		exit(0) ;
	add_history(ms->last_line);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_ms	*ms;

	ms = get_ms();
	ms_init(ms, envp);
	while (1)
	{
		prompter(ms);
		parse(envp, &ms);
		print_cmd_lst(ms->cmds);
		// exec(&data);
		free_lst(ms->cmds);
		ms->cmds = NULL;	
	}
	free(ms);
}
