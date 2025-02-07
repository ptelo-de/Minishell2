#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#include "minishell.h"

// A system call is an entry point into the Linux kernel. 
//void sigint_handler(int signum) {
//    t_shell*shell;

//    shell = get_shell();
//    shell->exit_status = 130;
//    printf("Ctrl+C\n");

//}

//void interactive_mode(void)
//{
//    struct sigaction sa_int;

//    sigemptyset(&sa_int.sa_mask);
//    sa_int.sa_handler = sigint_handler;
//    sa_int.sa_flags = SA_RESTART; //dar restart a system calls, fazer teste de zerar esta variavel
//    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
//        write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
//        //free all minishell memory
//        exit(1);
//    }

    // Ignora SIGQUIT (Ctrl+\)
/*    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
        perror("Erro ao ignorar SIGQUIT");
        exit(EXIT_FAILURE);
    }*/

//}

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