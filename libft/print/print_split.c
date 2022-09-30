#include "../libft.h"

void	print_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		ft_printf("%s\n", split[i]);
}
