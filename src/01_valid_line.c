/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:00:25 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/06 09:27:05 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*return 0 if something each side of pipe. 
Else return 1
*/
static int	valid_pipe(char *line)
{
	int	i;
	int	val;

	if (!line || ft_strlen(line) == 0)
		return (-1);
	val = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '|')
		{
			val += ft_isspace_r(line[i]);
			i++;
		}
		if (val == 0)
			return (1);
		val = 0;
		i++;
	}
	if (line[i - 1] == '|')
		return (1);
	return (0);
}

/*return 0 if quotes closed
Else return 1
*/
static int	valid_quotes(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = -1;
	s_quote = 0;
	d_quote = 0;
	while (line[++i])
	{
		if (line[i] == 39 && d_quote % 2 == 0)
			s_quote++;
		if (line[i] == 34 && s_quote % 2 == 0)
			d_quote++;
	}
	if (s_quote % 2 == 0 && d_quote % 2 == 0)
		return (0);
	return (1);
}

/*return 0 if valid line
Else return (1)
*/
int	valid_line(char *line)
{
	if (valid_pipe(line) != 0)
	{
		printf("%s%s\n", ERR_FIRST, ERR_LINE_PIPE);
		return (1);
	}
	if (valid_quotes(line) != 0)
	{
		printf("%s%s\n", ERR_FIRST, ERR_LINE_QUOTE);
		return (1);
	}
	return (0);
}
