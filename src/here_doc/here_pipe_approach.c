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


//int main(int ac, char **av, char **envp)
//{
//	int pid;
//	int fd[2];
//	char *args[]= {"cat", NULL};
//	int exit_status;

//	fd[0] = open("a.txt", O_RDONLY);
//	fd[1] = open("b.txt", O_TRUNC | O_WRONLY | O_CREAT, 0644);
//	pid = fork();
//	waitpid(pid, &exit_status, 0);
//	if (!fd[0] < 0  || fd[1] < 0)
//		printf("OPEN RAISED ERROR");
//	printf("before waitpid call pid: %d\n", pid);
//	printf("after waitpid call pid: %d\n", pid);
//	if (pid == 0) 
//	{
//		sleep(10);
//		printf("DO CHILD\n");
//		dup2(fd[0], 0);
//		dup2(fd[1], 1);
//		close(fd[0]);
//    	close(fd[1]);
//		execve("/bin/cat", args, envp);
//		write(2, "execve failed\n", 15);
//		exit(-1);
//	}
//	else
//	{
//		printf("DO PARENT\n");
//	}

//    close(fd[0]);
//    close(fd[1]);


//}

//__sighandler_t ctr(int)
//{
//	printf("\n");
//	return(0);
//}
// cat << eof!cat<<eof!cat<<eof
//void off_signals(void)//ignore
//{
//	signal(SIGINT, SIG_IGN);

//}
//void	on_signals(void)//heredoc
//{
//	signal(SIGINT, SIG_DFL);
//	signal(ctrl/, SIG_IGNOR);
//}

//good code

/*int hereDoc(char *del)
{
	int fd[2];
	t_shell *shell;

	shell = get_shell();
	if(!del)
		return -1;
	if(pipe(fd) == -1)
		return -2;
	int pid = fork();
	//off_signals();
	if(pid == 0)
	{
		//on_signals();
		close(fd[0]);
		char *line =readline(">");
		while(line && strcmp(line, del))
		{
			write(fd[1], line, strlen(line));
			free(line);
			line = readline(">");//lida com os sinais
		}
		if (!line)
			printf("minishell: warning: here-document at line 1 delimited by end-of-file( wanted \'%s\')\n", del);
		close(fd[1]);
		//free all memory
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &(shell->exit_status),0);
	//signal(SIGINT, ctr);

	return (fd[0]);
}

int main(void)
{
	int fd =hereDoc("fim");

	char buffer[11];

	buffer[10] = 0;

	while(read(fd,buffer,1) > 0)
		write(1,buffer, 1);
	close(fd);
	return(0);
}*/