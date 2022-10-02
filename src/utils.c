/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:28:28 by gvial             #+#    #+#             */
/*   Updated: 2022/09/29 18:28:29 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ms.h"

int	find_cmd_i(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (!have_sign(split[i])
			&& ((i == 0) || (i != 0 && !have_sign(split[i - 1]))
				|| (i != 0 && have_sign(split[i - 1])
					&& ft_strlen(split[i - 1]) > 1)))
			break ;
	}
	return (i);
}

int	have_sign(char *s)
{
	if (ft_strchr(s, '<') || ft_strchr(s, '>'))
		return (1);
	return (0);
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

void	free_lst(t_cmd *head)
{
	t_cmd	*tmp;

	if (head == NULL)
		return ;
	while (head)
	{
		free(head->cmd_path);
		free_split(head->args);
		free(head->fd_in);
		free(head->fd_out);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
