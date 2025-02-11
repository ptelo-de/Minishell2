#include "minishell.h"

void here_sigint(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART; //dar restart a system calls, fazer teste de zerar esta variavel
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
		//free all minishell memory
		exit(1);
	}
}