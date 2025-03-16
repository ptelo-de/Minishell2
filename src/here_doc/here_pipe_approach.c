
#include "minishell.h"
#include "parsing.h"
#include "executer.h"

int hereDoc(char *del)
{
	t_shell *shell;

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
		char *line =readline(">");
		while(line && strcmp(line, del))
		{
			write(shell->here_pipe[1], line, strlen(line));
			free(line);
			line = readline(">");//lida com os sinais
		}
		if (!line)
			printf("minishell: warning: here-document at line 1 delimited by end-of-file( wanted \'%s\')\n", del);
		close(shell->here_pipe[1]);
		free_atributes();
		free_lst(shell->env);	//acrescentei para nao haver erros qd se faz ctrl d
        free_lst(shell->exp);
		exit(0);
	}
	close(shell->here_pipe[1]);
	waitpid(pid, &(shell->exit_status),0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (!shell->sigint_flag)
	{
		close (shell->here_pipe[0]);
		shell->sigint_flag = 0;
		return (-1);
	}
	return (shell->here_pipe[0]);
}