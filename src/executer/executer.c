/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:25 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 17:11:53 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

/**
 * @brief Executes a single built-in command without forking.
 *
 * Redirects stdout to `cmd->fd_out` if necessary, executes the built-in,
 * and restores the original stdout afterward.
 *
 * @param cmd the command to execute.
 * 
 * @return void.
 */
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

/**
 * @brief Executes a command line with redirections and piping.
 *
 * Creates a pipe if there's a next command, forks a new process,
 * and handles input/output redirection and execution in the child process.
 *
 * @param shell the shell structure containing command data.
 * @param i the index of the current command in the list.
 * @param prev_pipe0 the read end of the previous pipe, if any.
 * 
 * @return void.
 */
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

/**
 * @brief Handles cleanup and pipe management in the parent process.
 *
 * Closes previous pipe if needed, updates the pipe for the next command,
 * and closes input/output file descriptors of the current command.
 *
 * @param shell the shell structure.
 * @param i the index of the current command.
 * @param prev_pipe0 pointer to the read end of the previous pipe.
 * 
 * @return void.
 */
static void	handle_parent(t_shell *shell, int i, int *prev_pipe0)
{
	if (*prev_pipe0)
	{
		close(*prev_pipe0);
		*prev_pipe0 = 0;
	}
	if (shell->cmd[i + 1] && infile_error(shell->cmd[i]) == 0
		&& shell->cmd[i]->arg[0])
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

/**
 * @brief Waits for all child processes to finish.
 *
 * Iterates through all commands, waits for any active child process,
 * and stores the final exit status in the shell structure.
 *
 * @param shell the shell structure.
 * 
 * @return void.
 */
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

/**
 * @brief Executes all commands in the shell with proper redirection, piping, and signal handling.
 *
 * Manages here-documents and redirections, determines if execution should
 * be handled via a single built-in or through forked processes with pipes.
 * Activates execution-mode signal handling via `exec_mode`, handles each command,
 * and waits for all child processes to terminate.
 *
 * @param shell the main shell structure.
 * 
 * @return void.
 */
void	executer(t_shell *shell)
{
	int		i;
	int		prev_pipe0;

	manage_hd(shell);
	if (shell->exit_status == 130)
		return ;
	manage_redir(&shell);
	i = 0;
	prev_pipe0 = 0;
	exec_mode();
	while (shell->cmd[i])
	{
		if (shell->cmd[i]->arg[0] && infile_error(shell->cmd[i]) == 0
			&& !shell->cmd[i]->out_error)
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
