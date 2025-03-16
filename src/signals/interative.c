

#include "minishell.h"

// A system call is an entry point into the Linux kernel. 
void sigint_handler(int signum) 
{
    t_shell *shell;
    shell = get_shell();
    shell->exit_status = 130;
    write(1, "\n",2);
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    (void)signum;
}

void	ignore_signal(int signal)
{
    struct sigaction sa;

	memset(&sa, 0, sizeof(sa)); 
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) || sigaction(signal, &sa, NULL))
    {
        write(2, "sigaction failed at interactive mode in SIGQUIT\n", 49);
       //free all minishell memory
        exit(1);
    }
}
void interactive_mode(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART; //dar restart a system calls, fazer teste de zerar esta variavel
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
		//free all minishell memory
		exit(1);
	}
	ignore_signal(SIGQUIT);
}


/*
sigaction mask:  
The mask in struct sigaction are signals that 
will be blocked (in the thread the signal handler executes in)
while the signal handler is running.
sigemptyset(&sa_int.sa_mask): ensures that no other signal, besides the signal
being handled in that sigaction struct is blocked while the signal is being 
handled. The signal being handled is blocked by the kernel automatically, meaning
it is not configurable by the mask atribute.




 */