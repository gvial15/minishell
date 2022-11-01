/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_valid_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:00:25 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/18 14:44:15 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*return 0 if something each side of pipe. 
Else return 1
*/
static int	valid_cmd(char *line)
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
			val += ft_iscmd_char(line[i]);
			i++;
		}
		if (val == 0)
			return (1);
		val = 0;
		i++;
	}
	if (line[i - 1] == '|' || line[i - 1] == '<' || line[i - 1] == '>')
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
	int	error;

	error = 0;
	if (valid_quotes(line) != 0)
		error = lineerr_quote;
	else if (ft_strnstr(line, "<<<<<", ft_strlen(line)))
		error = lineerr_4in;
	else if (ft_strnstr(line, "<<<<", ft_strlen(line)))
		error = lineerr_3in;
	else if (ft_strnstr(line, ">>>>", ft_strlen(line)))
		error = lineerr_4out;
	else if (ft_strnstr(line, ">>>", ft_strlen(line)))
		error = lineerr_3out;
	else if (valid_cmd(line) != 0
		&& ft_strnstr(line, "|", ft_strlen(line)) != NULL)
		error = lineerr_pipe;
	else if (valid_cmd(line) != 0)
		error = lineerr_nocmd;
	return (print_line_err(error));
}

int	print_line_err(int error)
{
	if (error > 0)
	{
		printf("%s", ERR_FIRST);
		if (error == lineerr_quote)
			printf("%s\n", ERR_LINE_QUOTE);
		else if (error == lineerr_nocmd)
			printf("%s\n", ERR_LINE_NOCMD);
		else
		{
			printf("%s", ERR_SYNTAX_ERROR);
			if (error == lineerr_pipe)
				printf("%s\n", ERR_LINE_PIPE);
			if (error == lineerr_4in)
				printf("%s\n", ERR_LINE_5IN);
			if (error == lineerr_3in)
				printf("%s\n", ERR_LINE_4IN);
			if (error == lineerr_4out)
				printf("%s\n", ERR_LINE_4OUT);
			if (error == lineerr_3out)
				printf("%s\n", ERR_LINE_3OUT);
		}
	}
	return (error);
}

int	valid_line_error_conversion(int valid_line_return)
{
	if (valid_line_return == lineerr_quote)
		return (1);
	else if (valid_line_return == lineerr_nocmd)
		return (0);
	else
		return (258);
}
