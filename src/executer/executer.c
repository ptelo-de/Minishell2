/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:44:40 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/29 20:46:58 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that handles when there's only a build_in to be executed 

static void	perform_single_build_in(t_cmd *cmd)
{
	int	orig_stdout;

	if (cmd->fd_out > 1)
	{
		orig_stdout = dup(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	build_ins(cmd);
	if (cmd->fd_out > 1)
	{
		dup2(orig_stdout, STDOUT_FILENO);
		close(orig_stdout);
	}
}

//fucntion that executes a command line with its redirections

static void	execute_cmd_line(t_shell *shell, int i, int prev_pipe0)
{
	if (shell->cmd[i + 1])
		pipe(shell->cmd[i]->pipe);
	shell->cmd[i]->pid = fork();
	if (shell->cmd[i]->pid == -1)
		perror("Error fork");
	if (shell->cmd[i]->pid == 0)
	{
		handle_cmd_input(shell, i, prev_pipe0);
		handle_cmd_output_and_execute(shell, i, prev_pipe0);
	}
}

//fucntion that closes and updates variables in the parent process

static void	handle_parent(t_shell *shell, int i, int *prev_pipe0)
{
	if (*prev_pipe0)
	{
		close(*prev_pipe0);
		*prev_pipe0 = 0;
	}
	if (shell->cmd[i + 1] && infile_error(shell->cmd[i]) == 0 && shell->cmd[i]->arg[0])
	{
		if (shell->cmd[i]->fd_out > 1)
			close(shell->cmd[i]->pipe[0]);
		else
			*prev_pipe0 = shell->cmd[i]->pipe[0];
		close(shell->cmd[i]->pipe[1]);
	}
	if (shell->cmd[i]->fd_in > 0)
		close(shell->cmd[i]->fd_in);
	if (shell->cmd[i]->fd_out > 1)
		close(shell->cmd[i]->fd_out);
}

//fucntion that does the waiting of the child processes while
//storing the last exit_status

static void	wait_loop(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i]->pid > 0)
		{
			waitpid(shell->cmd[i]->pid, &shell->exit_status, 0);
			if (WIFEXITED(shell->exit_status))
				shell->exit_status = WEXITSTATUS(shell->exit_status);
			else if (WIFSIGNALED(shell->exit_status))
				shell->exit_status = 128 + WTERMSIG(shell->exit_status);
		}
		i++;
	}
}

//executer function

void	executer(t_shell *shell)
{
	int		i;
	int		prev_pipe0;

	i = 0;
	manage_hd(shell);
	if (shell->exit_status == 130)
		return ;
	manage_redir(&shell);
	prev_pipe0 = 0;
	exec_mode();
	while (shell->cmd[i])
	{
		if (shell->cmd[i]->arg[0] && infile_error(shell->cmd[i]) == 0)
		{
			if (!shell->cmd[1] && is_build_in(shell->cmd[0]))
				perform_single_build_in(shell->cmd[i]);
			else
				execute_cmd_line(shell, i, prev_pipe0);
		}
		handle_parent(shell, i, &prev_pipe0);
		i++;
	}
	wait_loop(shell);
}
