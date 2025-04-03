/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:42:35 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:30:05 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Adds a variable to the export list in sorted order.
 *
 * Creates a new node with the prefix "declare -x " and inserts it
 * into the export list maintaining alphabetical order.
 *
 * @param exp pointer to the export list.
 * @param var the variable to add.
 * 
 * @return void.
 */
static void	put_export(t_list **exp, char *var)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = ft_lstnew(ft_strjoin("declare -x ", var));
	if (*exp == NULL)
		*exp = new_node;
	else if (ft_strncmp((*exp)->content, new_node->content,
			ft_strlen((*exp)->content)) > 0)
		ft_lstadd_front(exp, new_node);
	else
	{
		temp = *exp;
		while (temp->next != NULL)
		{
			if (ft_strncmp(temp->next->content, new_node->content,
					is_longer(temp->next->content, new_node->content)) > 0)
			{
				new_node->next = temp->next;
				temp->next = new_node;
				return ;
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

/**
 * @brief Updates the value of a variable in the export list.
 *
 * Searches for the variable by name and updates its content.
 * Behavior depends on flag `b`:
 * - 0: replace content with raw `var`
 * - 1: replace content with "declare -x " + `var`
 * - other: no update performed
 *
 * @param lst the list to update.
 * @param var_name the name of the variable (e.g., "VAR").
 * @param var the new full variable content (e.g., "VAR=value").
 * @param b the mode/flag controlling the update behavior.
 * 
 * @return 1 if the variable was updated, 0 otherwise.
 */
static int	update_exp_value(t_list **lst, char *var_name, char *var, int b)
{
	t_list	*temp;
	char	*lst_var;

	temp = *lst;
	while (temp != NULL)
	{
		lst_var = get_var_name(temp->content);
		if (ft_strncmp(lst_var, var_name, is_longer(lst_var, var_name)) == 0)
		{
			free(lst_var);
			free(var_name);
			if (b == 0 || b == 1)
				free(temp->content);
			if (b == 0)
				temp->content = ft_strdup(var);
			if (b == 1)
				temp->content = ft_strjoin("declare -x ", var);
			return (1);
		}
		free(lst_var);
		temp = temp->next;
	}
	return (0);
}

/**
 * @brief Updates the value of a variable in a list, if it exists.
 *
 * Wrapper around `update_exp_value` that extracts the variable name.
 * Updates the environment or export list according to the flag `b`.
 *
 * @param lst the list to update.
 * @param var the variable (e.g., "VAR=value") to update.
 * @param b update mode flag (passed to `update_exp_value`).
 * 
 * @return 1 if the variable was updated, 0 otherwise.
 */
static int	update_lst(t_list **lst, char *var, int b)
{
	char	*var_name;

	if (!lst || !(*lst) || !var)
		return (0);
	var_name = get_var_name(var);
	if (update_exp_value(lst, var_name, var, b))
		return (1);
	free(var_name);
	return (0);
}

/**
 * @brief Prints all variables in the export list.
 *
 * Iterates through the export list and prints each variable.
 *
 * @param exp the export list.
 * 
 * @return void.
 */
static void	print_exp(t_list *exp)
{
	while (exp != NULL)
	{
		printf("%s\n", (char *)exp->content);
		exp = exp->next;
	}
}

/**
 * @brief Executes the `export` command.
 *
 * If no arguments are given, prints the export list. Otherwise, it adds or updates
 * variables in both the environment and export lists. Handles quotes and variable
 * formatting internally. Invalid arguments result in an error.
 *
 * @param env pointer to the environment list.
 * @param exp pointer to the export list.
 * @param cmd the command with export arguments.
 * 
 * @return 0 if all arguments were processed successfully, 1 if any were invalid.
 */
int	ms_export(t_list **env, t_list **exp, t_cmd *cmd)
{
	int		i;
	char	*arg_with_quotes;

	if (cmd->n_arg == 1)
		print_exp(*exp);
	i = 1;
	while (i < cmd->n_arg)
	{
		if (!arg_valid(cmd->arg[i]))
			return (1);
		else if (has_equal(cmd->arg[i]))
		{
			arg_with_quotes = put_double_quotes(cmd->arg[i]);
			if (!update_lst(env, cmd->arg[i], 0))
				ft_lstadd_back(env, ft_lstnew(ft_strdup(cmd->arg[i])));
			if (!update_lst(exp, arg_with_quotes, 1))
				put_export(exp, arg_with_quotes);
			free(arg_with_quotes);
		}
		else if (!update_lst(exp, cmd->arg[i], 2))
			put_export(exp, cmd->arg[i]);
		i++;
	}
	return (0);
}
