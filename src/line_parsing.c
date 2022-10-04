#include "../include/minishell.h"

//return if position in line str is inside quote(return 1) or outside(return 0)
int	in_quotes(char *line, int position)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = -1;
	s_quote = 0;
	d_quote = 0;
	while (++i < position)
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

//return 0 if all first open quote have a closing one else return 1
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

/* if meta, return ascii char or if two char meta, char * char else return -1
cover meta | < << > >> $ */
int	meta_case(char *line)
{
	static char	*meta_list = "|<>$";
	int			ret_val;

	if (ft_strrchr_i(meta_list, line[0]) >= 0)
	{
		if ((line[0] == line[1] && (line[1] == '<' || line['>'])))
			return ((int)line[0] * (int)line[1]);
		return ((int)line[0]);
	}
	return (-1);
}

//return 0 if valid error code else
int	valid_line(char *line)
{
	if (!line || ft_strlen(line) == 0);
		return (1);
	if (valid_quotes(line) != 0)
		//error quote;
	//
	

}



void	tokeniser(char *line)
{
	int	i
}


