/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:49 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:44:09 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Adds double quotes around the value of an environment variable.
 *
 * Converts a string in the form `VAR=value` to `VAR="value"`.
 * Useful for formatting export output.
 *
 * @param str the original environment variable string.
 * 
 * @return a newly allocated string with the value quoted, or NULL on failure.
 */
char	*put_double_quotes(char *str)
{
	char	*with_quotes;
	int		i;

	if (!str)
		return (NULL);
	with_quotes = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!with_quotes)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		with_quotes[i] = str[i];
		i++;
	}
	with_quotes[i++] = '=';
	with_quotes[i++] = '"';
	while (str[i - 1])
	{
		with_quotes[i] = str[i - 1];
		i++;
	}
	with_quotes[i++] = '"';
	with_quotes[i] = '\0';
	return (with_quotes);
}

/**
 * @brief Checks if a string is already present in an array of strings.
 *
 * Compares the given string to all entries in `env_order` using
 * `ft_strncmp` up to the length of the longer string.
 *
 * @param str the string to check.
 * @param env_order the array of strings to check against.
 * 
 * @return 1 if the string is already present, 0 otherwise.
 */
static int	is_repeated(char *str, char **env_order)
{
	int	i;

	i = 0;
	while (env_order[i])
	{
		if (ft_strncmp(str, env_order[i], is_longer(str, env_order[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Finds the alphabetically smallest environment variable not yet added.
 *
 * Skips any variable already in `env_order` and ignores the one starting with `"_="`.
 * Returns the smallest variable name from `envp` based on alphabetical order.
 *
 * @param env_order the array of already ordered variables.
 * @param envp the full list of environment variables.
 * 
 * @return pointer to the smallest variable not yet added.
 */
static char	*get_smallest(char **env_order, char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	while (is_repeated(envp[i], env_order))
		i++;
	temp = envp[i];
	while (envp[i])
	{
		if (!is_repeated(envp[i], env_order)
			&& ft_strncmp(envp[i], "_=", 2) != 0)
		{
			if (ft_strncmp(temp, envp[i], is_longer(temp, envp[i])) > 0)
				temp = envp[i];
		}
		i++;
	}
	return (temp);
}

/**
 * @brief Returns an array of environment variables in alphabetical order.
 *
 * Creates a new array with the contents of `envp` sorted lexicographically,
 * excluding the variable that starts with `"_="`.
 *
 * @param envp the original environment variable array.
 * 
 * @return a newly allocated array with variables sorted alphabetically, or NULL on failure.
 */
static char	**alpha_order(char **envp)
{
	char	**env_order;
	int		i;

	env_order = ft_calloc(arr_len(envp), sizeof(char *));
	if (!env_order)
		return (NULL);
	i = 0;
	while (i < arr_len(envp) - 1)
	{
		env_order[i] = ft_strdup(get_smallest(env_order, envp));
		if (!env_order[i])
		{
			free_arr(env_order);
			return (NULL);
		}
		i++;
	}
	env_order[i] = NULL;
	return (env_order);
}

/**
 * @brief Generates the export list (`exp`) from the environment (`envp`).
 *
 * Creates a lexicographically ordered export list where each variable
 * is formatted as `declare -x VAR="value"`. Frees the input `envp` at the end.
 *
 * @param envp the array of environment variables.
 * 
 * @return a linked list representing the export list, or NULL on failure.
 */
t_list	*get_exp(char **envp)
{
	char	**env_order;
	t_list	*exp;
	char	*with_quotes;
	int		i;

	env_order = alpha_order(envp);
	i = 0;
	exp = NULL;
	while (env_order[i])
	{
		with_quotes = put_double_quotes(env_order[i]);
		if (!with_quotes)
		{
			free_arr(env_order);
			return (NULL);
		}
		ft_lstadd_back(&exp, ft_lstnew(ft_strjoin("declare -x ", with_quotes)));
		free(with_quotes);
		i++;
	}
	free_arr(env_order);
	free_arr(envp);
	return (exp);
}
