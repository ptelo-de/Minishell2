/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:37:38 by bde-luce          #+#    #+#             */
/*   Updated: 2025/01/30 14:43:43 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_list	*get_env(char **envp)
{
	t_list	*env;
	int			i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (env);
}

char	*put_double_quotes(char *str)
{
	int		l;
	char	*with_quotes;
	int		i;

	l = ft_strlen(str);
	with_quotes = calloc(l + 3, sizeof(char));
	i = 0;
	while (str[i] != '=')
	{
		with_quotes[i] = str[i];
		i++;
	}
	with_quotes[i] = str[i];
	i++;
	with_quotes[i] = '"';
	i++;
	while (str[i - 1])
	{
		with_quotes[i] = str[i - 1];
		i++;
	}
	with_quotes[i] = '"';
	return (with_quotes);
}

int	is_longer(char	*str1, char	*str2)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(str1);
	l2 = ft_strlen(str2);
	if (l1 > l2)
		return (l1);
	return (l2);
}

int	is_repeated(char *str, char **env_order)
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

char	*get_smallest(char **env_order, char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	while (is_repeated(envp[i], env_order))
		i++;
	temp = envp[i];
	while (envp[i])
	{
		if (!is_repeated(envp[i], env_order) && ft_strncmp(envp[i], "_=", 2) != 0)
		{
			if (ft_strncmp(temp, envp[i], is_longer(temp, envp[i])) > 0)
				temp = envp[i];
		}
		i++;
	}
	return (temp);
}

int	arr_len(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char **alpha_order(char **envp)
{
	char	**env_order;
	int		i;

	env_order = calloc(arr_len(envp), sizeof(char *)); // -1 de menos 1 var +1 de str nula = 0
	if (!env_order)
		return (NULL); //ver se quero melhorar este error heandling
	i = 0;
	while (i < arr_len(envp) - 1) // -1 porque exp tem menos 1 var que o env (não tem o "_=")
	{
		env_order[i] = ft_strdup(get_smallest(env_order, envp));
		i++;
	}
	env_order[i] = NULL;
	return (env_order);
}

t_list	*get_exp(char **envp)
{
	char	**env_order;
	t_list	*exp;
	char	*var_with_quotes;
	int		i;

	env_order = alpha_order(envp);
	i = 0;
	exp = NULL;
	while (env_order[i])
	{
		var_with_quotes = put_double_quotes(env_order[i]);
		ft_lstadd_back(&exp, ft_lstnew(ft_strjoin("declare -x ", var_with_quotes))); //maybe mudar nome funcao var_with_quotes para algo mais pequeno
		free(var_with_quotes);
		i++;
	}
	free_arr(env_order);
	return (exp);
}

/*int	repeated_n(char arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}*/

//alterar pwd para usar getcwd e assim ficar mais simples

/*static void	ms_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->arg[1] && (ft_strncmp(cmd->arg[1], "-n", ft_strlen(cmd->arg[1])) == 0 || repeated_n(cmd->arg[1])))
		i = 2;
	while (i < arr_len(cmd->arg))
	{
		printf("%s", cmd->arg[i]);
		i++;
		if (cmd->arg[i])
			printf(" ");
	}
	if (cmd->arg[1] && (ft_strncmp(cmd->arg[1], "-n", ft_strlen(cmd->arg[1])) != 0 || repeated_n(cmd->arg[1])))
		printf("\n");
}*/

/*static void	ms_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putendl_fd("Error: Failed to get current directory\n", 2);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}*/

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

void	put_export_mid_end(t_list **exp, char *var, t_list *new_node)
{
	t_list	*temp;
	char	*trim1;
	char	*trim2;
	
	temp = *exp;
	while (temp->next != NULL)
		{
			trim1 = ft_strtrim(temp->content, "declare -x ");
			trim2 = ft_strtrim(temp->next->content, "declare -x ");
			if (ft_strncmp(trim1, var, ft_strlen(var)) < 0 && ft_strncmp(trim2, var, ft_strlen(var)) > 0)
			{
				new_node->next = temp->next;
				temp->next = new_node;
				free(trim1);
				free(trim2);
				return;
			}
			temp = temp->next;
			free(trim1);
			free(trim2);
		}
		temp->next = new_node;
}

void	put_export(t_list **exp, char *var)
{
	t_list	*new_node;
	char	*var_join;
	char	*trim1;

	var_join = ft_strjoin("declare -x ", var);
	new_node = ft_lstnew(var_join);
	if (*exp == NULL)
	{
		*exp = new_node;
		return;
	}
	trim1 = ft_strtrim((*exp)->content, "declare -x ");
	if (ft_strncmp(trim1, var, ft_strlen(var)) > 0)
		ft_lstadd_front(exp, new_node);
	else
		put_export_mid_end(exp, var, new_node);
	free(trim1);
}

char	*trim_value(char *var)
{
	int 	i;
	char	*trim;

	i = 0;
	while (var[i] != '=')
		i++;
	trim = ft_calloc(i + 1, sizeof(char));
	trim = ft_strlcpy(trim, var, sizeof(char) * (i + 1));
	return (trim);
}

void	update_env(t_list **env, char *var)
{
	t_list	*temp;
	char	*trim;
	
	temp = *env;
	while (temp != NULL)
	{
		trim = trim_value(var);
		if (ft_strncmp(temp->content, trim, ft_strlen(trim)) == 0)
		{
			free(trim);
			free(temp->content);
			temp->content = ft_strdup(var);
			return;
		}
		(*env) = (*env)->next;
	}
}

void	ms_export(t_list **env, t_list **exp, char *var)
{
	char	*var_with_quotes;
	
	if (has_equal(var))
	{
		
		ft_lstadd_back(env, ft_lstnew(ft_strdup(var)));
		var_with_quotes = put_double_quotes(var);
		put_export(exp, var_with_quotes);
		free(var_with_quotes);
	}
	else
		put_export(exp, var);
}

void	delete_var(t_list **lst, char *var)
{
	t_list	*temp;
	t_list	*to_delete;
	
	temp = *lst;
	while (temp->next && ft_strncmp(temp->next->content, var, ft_strlen(var)) != 0)
		temp = temp->next;
	if (temp->next && ft_strncmp(temp->next->content, var, ft_strlen(var)) == 0)
	{
		to_delete = temp->next;
		temp->next = temp->next->next;
		free(to_delete->content);
		free(to_delete);
	}
}

//mudar parametro do unset para receber struct cmd com lista de args e fazer um while loop que corre os args e faz unset de cada

void	ms_unset(t_list **env, t_list **exp, char *var)
{
	char	*var_join_env;
	char	*var_join_exp;

	var_join_env = ft_strjoin(var, "=");
	var_join_exp = ft_strjoin("declare -x ", var_join_env);
	delete_var(env, var_join_env);
	delete_var(exp, var_join_exp);
	free(var_join_env);
	free(var_join_exp);
}

void	ms_env(t_list *env)
{
	while (env != NULL)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

void	free_lst(t_list *lst)
{
	t_list	*temp;
	
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->content);
		free(temp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	//t_list	*temp;
	//t_list	*temp2;
	//t_list	*exp;

	env = get_env(envp);
	//exp = get_exp(envp);
	//temp = env;
	//temp2 = exp;
	/*while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}
	printf("\n\n\n");
	ms_unset(&env, &exp, "NAME");
	temp = env;
	temp2 = exp;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}*/
	//ms_unset(&env, &exp, "NAME");
	//ms_env(env);
	/*temp2 = exp;
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}
	printf("\n\n\n");*/
	//ms_export(&env, &exp, "XXX=2");
	/*temp2 = exp;
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}
	printf("\n\n\n");*/
	ms_env(env);
	free_lst(env);
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	//free_lst(exp);
	(void)argc;
	(void)argv;
}


/*void	executer()
{
	t_shell	*shell;
	int		i;

	shell = get_shell();
	i = 0;
	while (shell->cmd[i])
	{
		if (ft_strncmp(shell->cmd[i]->arg[0], "echo", 4) == 0)
			ms_echo(shell->cmd[i]);
		//if (ft_strncmp(shell->cmd[i]->arg[0], "pwd", 3) == 0)
		//	ms_pwd(shell->env);
		i++;
	}
}*/



/*t_list	*env;
	t_list	*temp;
	t_list	*temp2;
	t_list	*exp;

	env = get_env(envp);
	exp = get_exp(envp);
	temp = env;
	temp2 = exp;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}
	printf("\n\n\n");
	ms_unset(&env, &exp, "NAME");
	temp = env;
	temp2 = exp;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	while (temp2 != NULL)
	{
		printf("%s\n", (char *)temp2->content);
		temp2 = temp2->next;
	}*/


	
/*static void	ms_pwd(t_list *env)
{
	char	*trim;

	while (env != NULL)
	{
		if (ft_strncmp(env->content, "PWD=", 4) == 0)
		{
			trim = ft_strtrim(env->content, "PWD=");
			if (trim == 0)
				ft_putendl_fd("Error: Memory allocation failed\n", 2);
			else
			{
				printf("%s\n", trim);
				free(trim);
			}
			return;
		}
		env = env->next;
	}
	ft_putendl_fd("Error: Unable to find PWD in environment variables\n", 2);
	return;
}*/