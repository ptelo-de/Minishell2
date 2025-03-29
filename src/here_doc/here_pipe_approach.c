#include "minishell.h"
#include "parsing.h"
#include "executer.h"

int hereDoc(char *del, t_type expantion_rule)
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
			if (expantion_rule !=  QUOTE)
				here_expander(&line);
			write(shell->here_pipe[1], line, safe_strlen(line));
			write(shell->here_pipe[1], "\n", 1);
			free(line);
			line = readline(">");//lida com os sinais
		}
		if (!line)
			printf("minishell: warning: here-document at line 1 delimited by end-of-file( wanted \'%s\')\n", del);
		
		close(shell->here_pipe[1]);
		ms_exit(&shell, NULL);
	}
	close(shell->here_pipe[1]);
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (shell->exit_status == 130)								//do not delete BERNARDO WAS HERE
		close(shell->here_pipe[0]);
	return (shell->here_pipe[0]);
}

//function that stores the value of the last heredoc fd in fd_in in each command

void	manage_hd(t_shell *shell)
{
	int		i;
	int		j;
	int		fd_hd;

	i = -1;
	while (shell->cmd[++i])
	{
		j = -1;
		fd_hd = 0;
		while (shell->cmd[i]->red[++j])
		{
			if (shell->cmd[i]->red[j]->type == HERE_DOC)
			{
				if (fd_hd != 0)
					close(fd_hd);
				fd_hd = hereDoc(shell->cmd[i]->red[j]->str, shell->cmd[i]->red[j]->expantion_rule);
				if (infile_error(shell->cmd[i]))
					close(fd_hd);
				if (shell->exit_status == 130 || fd_hd < 0)
					return;
			}
		}
		if (!infile_error(shell->cmd[i]))
			shell->cmd[i]->fd_in = fd_hd;
	}
}
