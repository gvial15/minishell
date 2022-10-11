/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:46 by gvial             #+#    #+#             */
/*   Updated: 2022/10/11 10:06:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_heredoc(int *heredoc)
{
	int	i;

	if (heredoc[0] == -1)
		return (printf("heredoc: (null)\n"));
	printf("heredoc: ");
	i = -1;
	while (heredoc[++i] != -1)
		printf("%i ", heredoc[i]);
	printf("\n");
	return (0);
}

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
		printf("fd_in:\n");
		print_split(head->fd_in);
		printf("fd_out: \n");
		print_split(head->fd_out);
		printf("append:%i\n", head->append);
		print_heredoc(head->heredoc);
		head = head->next;
		i++;
	}
}
/************^^^^^testing functions^^^^^************/

static int	prompter(t_ms *ms)
{
	ms->last_line = readline(ms->line_prompt);
	while (ms->last_line && (ft_strlen(ms->last_line) == 0
			|| ft_isallspace(ms->last_line)))
		ms->last_line = readline(ms->line_prompt);
	if (ft_strnstr(ms->last_line, "exit", 4))
		exit (0);
	add_history(ms->last_line);
	return (valid_line(ms->last_line));
}

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;

	(void) ac;
	(void) av;
	ms = get_ms();
	ms_init(ms, envp);
	while (1)
	{
		if (prompter(ms) == 0)
		{
			parse(envp, ms);
			print_cmd_lst(ms->cmds);
			free_cmds(ms->cmds);
			exec(ms);
		}
		ms->cmds = NULL;
	}
	free(ms);
}
