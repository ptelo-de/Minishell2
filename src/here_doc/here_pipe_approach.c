/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_pipe_approach.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:51:40 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 23:45:15 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

/**
 * @brief catches user input for here doc.
 *
 * generates readline loop, and writes input in command's
 * here_pipe[1].
 * Input is expanded according to bash rules for here doc
 *
 * @param del is delimiter for here doc.
 * @param rule if it is QUOTE it will expand input, otherwise it will not.
 * @return void.
 */
void	catch_here_input(char *del, t_type rule)
{
	char	*line;
	t_shell	*shell;

	shell = get_shell();
	line = readline(">");
	while (line && strcmp(line, del))
	{
		if (rule != QUOTE)
			here_expander(&line);
		write(shell->here_pipe[1], line, safe_strlen(line));
		write(shell->here_pipe[1], "\n", 1);
		if (line)
			free(line);
		line = readline(">");
	}
	if (!line)
		printf("minishell: warning: here-document at line \
		1 delimited by end-of-file( wanted \'%s\')\n", del);
	else if (line)
		free(line);
}

/**
 * @brief Preforms here doc according to bash rules.
 * If sigint is recieved during here doc, the function returns a closed fd.
 * @param del here doc delimeter;
 * @param rule if it is QUOTE it will expand input, otherwise it will not.
 * @return file descriptor, type pipe, where here is stored.
 */
int	here_doc(char *del, t_type expansion_rule)
{
	t_shell	*shell;
	int		pid;

	shell = get_shell();
	if (!del)
		return (-1);
	if (pipe(shell->here_pipe) == -1)
		return (-2);
	pid = fork();
	if (pid == 0)
	{
		close(shell->here_pipe[0]);
		here_sigint();
		catch_here_input(del, expansion_rule);
		close(shell->here_pipe[1]);
		ms_exit(&shell, NULL);
	}
	close(shell->here_pipe[1]);
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (shell->exit_status == 130)
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
				fd_hd = here_doc(shell->cmd[i]->red[j]->str, shell->cmd[i]->red[j]->expansion_rule);
				if (infile_error(shell->cmd[i]))
					close(fd_hd);
				if (shell->exit_status == 130 || fd_hd < 0)
					return ;
			}
		}
		if (!infile_error(shell->cmd[i]))
			shell->cmd[i]->fd_in = fd_hd;
	}
}
