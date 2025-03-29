/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_pipe_approach.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:51:40 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 02:31:17 by ptelo-de         ###   ########.fr       */
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
		free(line);
		line = readline(">");
	}
	if (!line)
		printf("minishell: warning: here-document at line \
		1 delimited by end-of-file( wanted \'%s\')\n", del);
}

/**
 * @brief Preforms here doc according to bash rules.
 * 
 * @param del here doc delimeter;
 * @param rule if it is QUOTE it will expand input, otherwise it will not.
 * @return file descripto, type pipe, where here is stored.
 */
int	here_doc(char *del, t_type expantion_rule)
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
		catch_here_input(del, expantion_rule);
		close(shell->here_pipe[1]);
		ms_exit(&shell, NULL, 1);
	}
	close(shell->here_pipe[1]);
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
	return (shell->here_pipe[0]);
}
