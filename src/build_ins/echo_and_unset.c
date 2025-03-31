/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:40:21 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/29 20:29:01 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that checks for the presence of flag -n in echo

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

//echo fucntion

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

//function that deletes a variable (node) from a list
//será preciso error handling (if (!lst || !(*lst)))

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

//unset function

int	ms_unset(t_list **env, t_list **exp, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (i < cmd->n_arg)
	{
		delete_var(env, cmd->arg[i]);
		delete_var(exp, cmd->arg[i]);
		i++;
	}
	return (0);
}
