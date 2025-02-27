
#include "minishell.h"
#include "parsing.h"
#include "executer.h"

int hereDoc(char *del)
{
	t_shell *shell;

	shell = get_shell();
	if(pipe(shell->here_pipe) == -1)
		return -1;
	int pid = fork();
	if(pid == 0)
	{
		close(shell->here_pipe[0]);
		here_sigint(); //needs to clear heredoc
		char *line = readline(">");
		while(line && strcmp(line, del))
		{
			write(shell->here_pipe[1], line, strlen(line));
			write(shell->here_pipe[1], "\n", 1);
			free(line);
			line = readline(">");//lida com os sinais
		}
		free(line);
		if (!line)
			printf("minishell: warning: here-document at line 1 delimited by end-of-file( wanted \'%s\')\n", del);
		close(shell->here_pipe[1]);
		free_atributes();
		free_lst(shell->env);
    	free_lst(shell->exp);
		exit(0);
	}
	waitpid(pid, &(shell->exit_status),0);
	close(shell->here_pipe[1]);
	if (shell->sigint_flag)
	{
		close(shell->here_pipe[0]);
		shell->sigint_flag = 0;
		return (0);
	}
	return (shell->here_pipe[0]);
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