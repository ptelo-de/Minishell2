#include "executer.h"
#include "parsing.h"

void here_sigint_handler(int signum)
{
	t_shell	*shell;
	
	shell = get_shell();
	(void)signum;
	shell->sigint_flag = 1;
	close(shell->here_pipe[1]);
	shell->exit_status = 130;
	ms_exit(&shell, NULL, 1);
}
void here_sigint(void)
{
	struct sigaction sa;

	sa.sa_handler = here_sigint_handler;
	sa.sa_flags = SA_RESTART; //dar restart a system calls, fazer teste de zerar esta variavel
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
		//free all minishell memory
		exit(1);
	}
}