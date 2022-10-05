#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
}

void	prompter(t_ms* ms)
{
	ms->last_line = readline(" >> ");
	add_history(ms->last_line);
}