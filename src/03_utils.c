/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:28 by gvial             #+#    #+#             */
/*   Updated: 2022/10/07 17:36:57 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	have_redirec(char *s)
{
	if (s[0] == '<' || s[0] == '>')
		return (1);
	return (0);
}

int	have_dbl_redirec(char *s)
{
	if (ft_strnstr(s, ">>", 2) || ft_strnstr(s, "<<", 2))
		return (1);
	return (0);
}

int	find_cmd_i(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (!have_redirec(split[i]))
		{
			if (i == 0)
				break;
			if (i > 1 && !have_redirec(split[i - 1]) && have_dbl_redirec(split[i - 2])
				&& ft_strlen(split[i - 2]) == 2)
				break ; // >> out cmd
			if (i > 1 && !have_redirec(split[i - 1]) && have_redirec(split[i - 2])
				&& ft_strlen(split[i - 2]) == 1)
				break ; // > out cmd
			if (have_redirec(split[i - 1]) && ft_strlen(split[i - 1]) > 1
				&& !have_dbl_redirec(split[i - 1]))
				break ; // >out cmd
			if (have_dbl_redirec(split[i - 1]) && ft_strlen(split[i - 1]) > 2)
				break ;	// >>out cmd
		}
	}
	return (i);
}

t_cmd	*lst_last(t_cmd *head)
{
	if (!head)
		return (head);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int	lst_len(t_cmd *head)
{
	int	len;

	if (!head)
		return (0);
	len = 1;
	while (head && head->next != NULL)
	{
		len++;
		head = head->next;
	}
	return (len);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd == NULL)
		return ;
	while (cmd)
	{
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->fd_in)
			free(cmd->fd_in);
		if (cmd->fd_out)
			free_split(cmd->fd_out);
		if (cmd->heredoc)
			free(cmd->heredoc);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
