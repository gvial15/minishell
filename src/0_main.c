#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = getms();
	ms_init(ms, envp);
	while (1)
	{
		prompter(ms);
	}
	return (0);
}

void	prompter(t_ms *ms)
{
	ms->last_line = readline(" >> ");
	add_history(ms->last_line);
}