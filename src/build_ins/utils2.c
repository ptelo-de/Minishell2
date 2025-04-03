/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:13:10 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:55:39 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Checks if a string contains the '=' character.
 *
 * Useful for detecting if a variable includes a value assignment.
 *
 * @param var the string to check.
 * 
 * @return 1 if '=' is found, 0 otherwise.
 */
int	has_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Extracts the name of a variable from a declaration string.
 *
 * Handles input in the form `declare -x VAR=value` or `VAR=value`
 * and returns only the variable name (`VAR`).
 *
 * @param var the full variable declaration.
 * 
 * @return a newly allocated string containing the variable name, or NULL on failure.
 */
char	*get_var_name(char *var)
{
	int		i;
	char	*no_prefix;
	char	*var_name;

	if (!var)
		return (NULL);
	i = 0;
	no_prefix = trim_prefix(var, "declare -x ");
	while (no_prefix[i] && no_prefix[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, no_prefix, sizeof(char) * (i + 1));
	free(no_prefix);
	return (var_name);
}

/**
 * @brief Frees a linked list of environment or export variables.
 *
 * Iterates through the list and frees each node and its content.
 * Safely handles NULL input.
 *
 * @param lst the list to free.
 * 
 * @return void.
 */
void	free_lst(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->content);
		free(temp);
	}
}

/**
 * @brief Frees all memory associated with the shell before exiting.
 *
 * Frees environment and export lists, readline buffer, and shell attributes.
 * Should be called before program termination to avoid memory leaks.
 *
 * @return void.
 */
void	free_all(void)
{
	t_shell	*shell;

	shell = get_shell();
	free_atributes();
	if (shell->readline)
		free(shell->readline);
	free_lst(shell->env);
	free_lst(shell->exp);
}

/**
 * @brief Checks if an export argument is a valid variable identifier.
 *
 * Valid identifiers must start with a letter or underscore and may be followed
 * by letters, digits, or underscores. Stops checking at the '=' character.
 *
 * @param arg the argument to validate.
 * 
 * @return 1 if the identifier is valid, 0 otherwise. Prints an error if invalid.
 */
int	arg_valid(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		printf("Error: export: '%s': not a valid identifier\n", arg);
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("Error: export: '%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}
