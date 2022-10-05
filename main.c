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

static void	init_data(t_data **data, char **envp)
{
	(*data) = malloc(sizeof(t_data) * 1);
	(*data)->cmds = NULL;
	(*data)->last_line = NULL;
	(*data)->envp = envp;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 1)
		return (0);
	init_data(&data, envp);
	while (1)
	{
		data->last_line = readline("$> ");
		if (ft_strnstr(data->last_line, "exit", 4))
			break ;
		if (data->last_line)
		{
			add_history(data->last_line);
			parse(envp, &data);
			print_cmd_lst(data->cmds);
			// exec(&data);
			free_lst(data->cmds);
			data->cmds = NULL;
		}
	}
	free(data);
}
