/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:13:10 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 14:02:10 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that checks if there's an "=" in a string

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

//function that gives the name of var
//(declare -x SHLVL=1 or SHLVL=1 become SHLVL)

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

//function that frees a list

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

//function that frees everything that is needed before leaving the program

void	free_all(void)
{
	t_shell	*shell;

	shell = get_shell();
	free_atributes();
	free(shell->readline);
	free_lst(shell->env);
	free_lst(shell->exp);
}
