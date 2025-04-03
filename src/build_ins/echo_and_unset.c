/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:40:21 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:13:23 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Checks if a given argument is the `-n` flag.
 *
 * Verifies if the argument starts with '-' and is followed only by 'n' characters.
 * Used to determine if echo should suppress the trailing newline.
 *
 * @param arg the argument string to check.
 * 
 * @return 1 if it is a valid -n flag, 0 otherwise.
 */
static int	flag_n(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Executes the `echo` command.
 *
 * Prints the given arguments to standard output. If one or more `-n` flags
 * are present at the beginning, it suppresses the trailing newline.
 *
 * @param cmd the command containing the arguments to be echoed.
 * 
 * @return 0 (always successful).
 */
int	ms_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (flag_n(cmd->arg[i]))
		i++;
	while (i < cmd->n_arg)
	{
		printf("%s", cmd->arg[i]);
		i++;
		if (cmd->arg[i])
			printf(" ");
	}
	if (!flag_n(cmd->arg[1]))
		printf("\n");
	return (0);
}

/**
 * @brief Deletes a variable from a linked list.
 *
 * Searches for a node matching the given variable name and removes it from the list.
 * Frees all associated memory. Handles deletion from the head or middle of the list.
 *
 * @param lst pointer to the environment or export list.
 * @param var the variable name to delete.
 * 
 * @return void.
 */
static void	delete_var(t_list **lst, char *var)
{
	t_list	*temp;
	t_list	*prev;
	char	*lst_var;

	temp = *lst;
	prev = NULL;
	while (temp)
	{
		lst_var = get_var_name(temp->content);
		if (ft_strncmp(lst_var, var, is_longer(lst_var, var)) == 0)
		{
			free(lst_var);
			if (!prev)
				*lst = (*lst)->next;
			else
				prev->next = temp->next;
			free(temp->content);
			free(temp);
			return ;
		}
		free(lst_var);
		prev = temp;
		temp = temp->next;
	}
}

/**
 * @brief Executes the `unset` command.
 *
 * Removes specified environment and export variables. If `PATH` is unset,
 * also clears the shell’s private path.
 *
 * @param env pointer to the environment list.
 * @param exp pointer to the export list.
 * @param cmd the command containing the arguments to unset.
 * 
 * @return 0 (always successful).
 */
int	ms_unset(t_list **env, t_list **exp, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (i < cmd->n_arg)
	{
		if (ft_strncmp(cmd->arg[i], "PATH", 5) == 0)
			get_shell()->private_path = NULL;
		delete_var(env, cmd->arg[i]);
		delete_var(exp, cmd->arg[i]);
		i++;
	}
	return (0);
}
