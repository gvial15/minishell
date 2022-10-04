

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	int	sig2;

	sig2 = sig;
	printf("%d\n", sig);
}

void	handle_sigquit(int sig)
{
	int	sig2;

	sig2 = sig;
	printf("yo %d\n", sig);
}

void	signal_handler(t_var *var)
{
	var->sa_quit.sa_handler = &handle_sigquit;
	sigaction(SIGQUIT, &var->sa_quit, NULL);
	var->sa_quit.sa_flags = 0;
	sigemptyset(&var->sa_quit.sa_mask);
	
	var->sa_int.sa_handler = &handle_sigint;
	sigaction(SIGINT, &var->sa_int, NULL);
	var->sa_int.sa_flags = 0;
	sigemptyset(&var->sa_int.sa_mask);

	
	//signal(SIGINT, &handle_sigtstp);
}

void	cmd_line_show(t_var *var)
{
	var->cmd_line = readline("   RBX_SHELL > ");
	add_history(var->cmd_line);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc > 1)
		write(1, NOARGALLOWED, ft_strlen(NOARGALLOWED));
	write(1, WELCOME, ft_strlen(WELCOME));
	signal_handler(&var);
	var.envp = envp;
	var.argv = argv;
	cmd_line_show(&var);
	return (0);
}
