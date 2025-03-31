/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:43:29 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 00:18:15 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//env function

static int	ms_env(t_list *env)
{
	while (env != NULL)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (0);
}

//function that checks if a string is only composed by digits

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

//exit function

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

void	close_pipes_for_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->pipe[0] > 2)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] > 2)
		close(cmd->pipe[1]);
}

//function that calls for the execution of a build_in

int	build_ins(t_cmd *cmd)
{
	t_shell	*shell;

	shell = get_shell();
	if (!cmd || !cmd->arg || !cmd->arg[0])
		return (0);
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
	else
		return (0);
	return (1);
}
