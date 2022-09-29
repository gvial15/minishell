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
		free(head->fd_in);
		free(head->fd_out);
		free(head->cmd_path);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
