/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:42:35 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/29 20:34:04 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that adds the variable to exp and/or env 
//lists in case it doesnt exist there

static void	put_export(t_list **exp, char *var)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = ft_lstnew(ft_strjoin("declare -x ", var));
	if (*exp == NULL)
		*exp = new_node;
	else if (ft_strncmp((*exp)->content, new_node->content, ft_strlen((*exp)->content)) > 0)
		ft_lstadd_front(exp, new_node);
	else
	{
		temp = *exp;
		while (temp->next != NULL)
		{
			if (ft_strncmp(temp->content, new_node->content, is_longer(temp->content, new_node->content)) < 0 && ft_strncmp(temp->next->content, new_node->content, is_longer(temp->next->content, new_node->content)) > 0)
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

//function that updates a variable value in exp and/or 
//env lists if it already exists there

static int	update_lst(t_list **lst, char *var, int b)
{
	t_list	*temp;
	char	*lst_var;
	char	*var_name;

	if (!lst || !(*lst) || !var)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		lst_var = get_var_name(temp->content);
		var_name = get_var_name(var);
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
		free(var_name);
		temp = temp->next;
	}
	return (0);
}

//funtion that prints exp list

static void	print_exp(t_list *exp)
{
	while (exp != NULL)
	{
		printf("%s\n", (char *)exp->content);
		exp = exp->next;
	}
}

//function that checks if a variable has a valid name

static int	arg_valid(char *arg)
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

//export function

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
