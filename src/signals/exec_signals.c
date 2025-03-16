#include "minishell.h"
#include "executer.h"


void	exec_handler(int signal)
{
	
	t_shell	*shell;
	
	shell = get_shell();
	
	if (signal == SIGQUIT)
		get_shell()->exit_status = 131;
	if (signal == SIGINT)
	{
		get_shell()->exit_status = 130;
		ms_exit(&shell, NULL, 0);
	}
}
void executer_mode(void)
{
	struct sigaction sa;

	sa.sa_handler = exec_handler;
	sa.sa_flags = SA_RESTART; //dar restart a system calls, fazer teste de zerar esta variavel
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
		//free all minishell memory
		exit(1);
	}
	ignore_signal(SIGQUIT);
}