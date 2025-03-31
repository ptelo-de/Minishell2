/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:49 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 17:18:14 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that puts the value of a variable in envp under double quotes
//(SHLVL=1 becomes SHLVL="1")

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

//function that checks if 2 strings are repeated (are the same)

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

//function that returns the smallest variable of envp, in alphabetical
//order, that is not already in env_order

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

//funtion that returns envp ordered alphabetically without
//the variable that starts with "_"

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

//function that generates exp from env

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
