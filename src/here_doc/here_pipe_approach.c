#include "minishell.h"
#include "parsing.h"
#include "executer.h"

int hereDoc(char *del)
{
	t_shell *shell;
	char *line;

	shell = get_shell();
	if(!del)
		return -1;
	if(pipe(shell->here_pipe) == -1)
		return -2;
	int pid = fork();
	if(pid == 0)
	{
		close(shell->here_pipe[0]);
		here_sigint(); //needs to clear heredoc
		line =readline(">");
		while(line && strcmp(line, del))
		{
			write(shell->here_pipe[1], line, strlen(line));
			write(shell->here_pipe[1], "\n", 1);
			free(line);
			line = readline(">");//lida com os sinais
		}
		if (!line)
			printf("minishell: warning: here-document at line 1 delimited by end-of-file( wanted \'%s\')\n", del);
		
		close(shell->here_pipe[1]);
		ms_exit(&shell, NULL, 1);
	}
	close(shell->here_pipe[1]);
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	return (shell->here_pipe[0]);
}