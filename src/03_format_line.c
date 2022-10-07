#include "../include/minishell.h"

int	need_space(char *last_line, int i)
{
	if (i != 0 && (last_line[i] == '>' || last_line[i] == '<'))
		if (last_line[i - 1] != ' ' && last_line[i - 1] != '<'
			&& last_line[i - 1] != '>')
			return (1);
	return (0);
}

static int	get_space_count(char *last_line)
{
	int	i;
	int	space_count;

	space_count = 0;
	i = -1;
	while (last_line[++i])
		if (need_space(last_line, i))
			space_count++;
	return (space_count);
}

// this space out the redirection if needed ex: ">out>>out2" = ">out >>out2"
char	*space_out_redirections(char *last_line)
{
	int		i;
	int		j;
	int		space_count;
	char	*new_last_line;

	space_count = get_space_count(last_line);
	if (space_count == 0)
		return (last_line);
	new_last_line = malloc(sizeof(char) * ft_strlen(last_line) + space_count + 1);
	j = 0;
	i = -1;
	while (last_line[++i])
	{
		if (need_space(last_line, i))
		{
			new_last_line[j++] = ' ';
			new_last_line[j++] = last_line[i];
		}
		else
			new_last_line[j++] = last_line[i];
	}
	new_last_line[j] = 0;
	free(last_line);
	return (new_last_line);
}
