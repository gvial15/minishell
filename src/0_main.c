
	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:27:46 by gvial             #+#    #+#             */
/*   Updated: 2022/10/13 10:18:52 by mraymond         ###   ########.fr       */
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
	ms_reset(ms);
	ms->last_line = readline(ms->line_prompt);
	while (ms->last_line && (ft_strlen(ms->last_line) == 0
			|| ft_isallspace(ms->last_line)))
	{
		ms_reset(ms);
		ms->last_line = readline(ms->line_prompt);
	}
	if (ms->last_line == NULL || ft_strnstr(ms->last_line, "exit", 4))
		history_clear_n_exit(ms);
	add_history(ms->last_line);
	return (valid_line(ms->last_line));
}

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;

	(void) ac;
	(void) av;
	ms = get_ms(0);
	ms_init(ms, envp);
	while (1)
	{
		if (prompter(ms) == 0)
		{
			parse(envp, ms);
			print_cmd_lst(ms->cmds);
			exec(ms);
			free_cmds(ms);
		}
		ms->cmds = NULL;
	}
}

void	history_clear_n_exit(t_ms *ms)
{
	write(1, "exit\n", 5);
	all_var_free(ms);
	exit(0);
}

void	all_var_free(t_ms *ms)
{
	ms_reset(ms);
	//free(ms->envp); lorsque version envp malloc sera merge
	get_ms(1);
	clear_history();
}
