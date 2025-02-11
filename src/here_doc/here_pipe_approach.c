
#include "minishell.h"


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

int hereDoc(char *del)
{
	int fd[2];
	t_shell *shell;

	shell = get_shell();
	if(!del)
		return -1;
	if(pipe(fd) == -1)
		return -2;
	int pid = fork();
	if(pid == 0)
	{
		here_sigint(); //needs to clear heredoc
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
/*

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