/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:00:25 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/05 15:32:34 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//return 0 if valid error code else
int	valid_line(char *line)
{
	if (valid_quotes(line) != 0)
		printf("error quote\n");
	if (valid_pipe(line) != 0)
		printf("error pipe\n");
}

//return 0 if something each side of pipe. Else return 1
int	valid_pipe(char *line)
{
	int	i;
	int	val;

	if (!line || ft_strlen(line) == 0)
		return (-1);
	val = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] != '|')
		{
			val += ft_isspace_r(line[i]);
			i++;
		}
		if (val == 0)
			return (1);
		val = 0;
		i++;
	}
	return (0);
}

int	valid_quotes(char *line)
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








//return char of quote content Need to confirm if one closing before using it
char	*quote_content(char *first_quote_position)
{
	int		i;
	char	*str_quote;

	i = len_next_quote(first_quote_position, first_quote_position[0]);
	str_quote = (char *)malloc(sizeof(char) * i);
	ft_strlcpy(str_quote, first_quote_position[1], i);
	return (str_quote);
}

//return the position of the second quote starting at first_quote_position
int	len_next_quote(char *first_quote_position, char quote)
{
	int	i;

	i = 1;
	while (first_quote_position[i] != quote)
		i++;
	return (i);
}