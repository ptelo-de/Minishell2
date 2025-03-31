/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_exec_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:54:07 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 14:07:31 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that handles the input of the command to be executed

void	handle_cmd_input(t_shell *shell, int i, int prev_pipe0)
{
	int		dev_null;

	if (shell->cmd[i]->fd_in > 0)
	{
		dup2(shell->cmd[i]->fd_in, STDIN_FILENO);
		close(shell->cmd[i]->fd_in);
	}
	else if (prev_pipe0)
	{
		dup2(prev_pipe0, STDIN_FILENO);
		close(prev_pipe0);
	}
	else if (i != 0)
	{
		dev_null = open("/dev/null", O_RDONLY);
		if (dev_null == -1)
		{
			perror("Error opening /dev/null");
			exit(1);
		}
		dup2(dev_null, STDIN_FILENO);
		close(dev_null);
	}
}

//function that frees and closes stuff to avoid leaks
//when execve fails or build_ins are executed

static void	error_exec(char *path, char **envp, int prev_pipe0)
{
	t_shell	*shell;

	shell = get_shell();
	if (path)
		free(path);
	free_arr(envp);
	if (prev_pipe0)
		close(prev_pipe0);
	ms_exit(&shell, NULL);
}

//fucntion that tries to execute a command/program

static void	exec_command(char **args, char **envp, int prev_pipe0)
{
	char	*path;

	path = create_path(args[0], envp);
	if (!path)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
	}
	else if (execve(path, args, envp) == -1)
		perror("execve error");
	error_exec(path, envp, prev_pipe0);
}

//funtion that closes all fd red from all the commands to avoid leaks

static void	close_all_fd_red(void)
{
	t_shell	*shell;
	int		i;

	shell = get_shell();
	i = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i]->fd_in > 0)
			close(shell->cmd[i]->fd_in);
		if (shell->cmd[i]->fd_out > 1)
			close(shell->cmd[i]->fd_out);
		i++;
	}
}

//funcntion that handles the output of the command
//to be executed and executes it

void	handle_cmd_output_and_execute(t_shell *shell, int i, int prev_pipe0)
{
	if (shell->cmd[i]->fd_out > 1)
	{
		dup2(shell->cmd[i]->fd_out, STDOUT_FILENO);
		close(shell->cmd[i]->fd_out);
	}
	else if (shell->cmd[i + 1])
		dup2(shell->cmd[i]->pipe[1], STDOUT_FILENO);
	if (prev_pipe0)
		close(prev_pipe0);
	if (is_build_in(shell->cmd[i]))
		build_ins(shell->cmd[i]);
	if (shell->cmd[i + 1])
	{
		close(shell->cmd[i]->pipe[0]);
		close(shell->cmd[i]->pipe[1]);
	}
	if (!is_build_in(shell->cmd[i]))
		exec_command(shell->cmd[i]->arg, make_env_arr(shell->env), prev_pipe0);
	close_all_fd_red();
	error_exec(NULL, NULL, 0);
}
