/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:43:29 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:25:02 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Executes the `env` command.
 *
 * Prints the current environment variables, one per line.
 *
 * @param env the environment list.
 * 
 * @return 0 (always successful).
 */
static int	ms_env(t_list *env)
{
	while (env != NULL)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (0);
}

/**
 * @brief Checks if a string is composed only of digits.
 *
 * Allows an optional leading '+' or '-' sign. Returns false
 * if any non-digit character is found after the sign.
 *
 * @param str the string to check.
 * 
 * @return 1 if the string is numeric, 0 otherwise.
 */
static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Executes the `exit` command with optional status handling.
 *
 * If no argument is given, exits with the current status. If one numeric argument
 * is provided, exits with that status. If too many arguments are passed, the function
 * prints an error and returns without exiting. If the argument is not numeric, an
 * error is shown and the status is set to 2 before exiting.
 *
 * @param shell pointer to the shell structure.
 * @param cmd the command containing optional arguments.
 * 
 * @return 1 if too many arguments are provided and the shell should continue running,
 * otherwise does not return (calls exit).
 */
int	ms_exit(t_shell **shell, t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->n_arg > 2 && str_isdigit(cmd->arg[1]))
			return (print_and_return("Error: exit: too many arguments", 1));
		else if (cmd->arg[1] && !str_isdigit(cmd->arg[1]))
		{
			printf("Error: exit: %s: numeric argument required\n", cmd->arg[1]);
			(*shell)->exit_status = 2;
		}
		else if (cmd->n_arg == 2 && str_isdigit(cmd->arg[1]))
			(*shell)->exit_status = ft_atoi(cmd->arg[1]);
	}
	free_all();
	exit((*shell)->exit_status);
}

/**
 * @brief Closes pipe file descriptors and prints "exit".
 *
 * Used before exiting the shell, ensures open pipe descriptors
 * are closed properly to prevent leaks.
 *
 * @param cmd the command whose pipe descriptors are to be closed.
 * 
 * @return void.
 */
void	close_pipes_for_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->pipe[0] > 2)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] > 2)
		close(cmd->pipe[1]);
}

/**
 * @brief Executes a built-in command if it matches one of the supported ones.
 *
 * Identifies and runs built-in commands such as `echo`, `cd`, `pwd`, `export`,
 * `unset`, `env`, and `exit`. Updates the shell’s exit status accordingly.
 * If the command is not a built-in or is invalid, does nothing.
 *
 * @param cmd the command to check and execute.
 * 
 * @return void.
 */
void	build_ins(t_cmd *cmd)
{
	t_shell	*shell;

	shell = get_shell();
	if (!cmd || !cmd->arg || !cmd->arg[0])
		return ;
	else if (ft_strncmp(cmd->arg[0], "echo", 5) == 0)
		shell->exit_status = ms_echo(cmd);
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		shell->exit_status = ms_cd(shell, &shell->env, cmd);
	else if (ft_strncmp(cmd->arg[0], "pwd", 4) == 0)
		shell->exit_status = ms_pwd();
	else if (ft_strncmp(cmd->arg[0], "export", 7) == 0)
		shell->exit_status = ms_export(&shell->env, &shell->exp, cmd);
	else if (ft_strncmp(cmd->arg[0], "unset", 6) == 0)
		shell->exit_status = ms_unset(&shell->env, &shell->exp, cmd);
	else if (ft_strncmp(cmd->arg[0], "env", 4) == 0)
		shell->exit_status = ms_env(shell->env);
	else if (ft_strncmp(cmd->arg[0], "exit", 5) == 0)
	{
		close_pipes_for_exit(cmd);
		shell->exit_status = ms_exit(&shell, cmd);
	}
}
