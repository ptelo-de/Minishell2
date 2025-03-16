/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:37:38 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/12 14:57:16 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
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
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

char	*trim_beggining(char *str, char *set)
{
	size_t	start;
	char	*trim;
	
	start = 0;
	if (ft_strncmp(str, set, ft_strlen(set)) == 0)
		start += ft_strlen(set);
	trim = ft_substr(str, start, ft_strlen(str) - start);
	if (!trim)
		return (NULL);
	return (trim);
}

t_list	*get_env(char **envp)
{
	t_list	*env;
	int		i;
	char	*dup;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		dup = ft_strdup(envp[i]);
		if (!dup)
		{
			free_lst(env);
			return (NULL);
		}
		ft_lstadd_back(&env, ft_lstnew(dup));
		i++;
	}
	return (env);
}

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
	if (has_equal(str))
	{
		while (str[i] != '=')
		{
			with_quotes[i] = str[i];
			i++;
		}
		with_quotes[i] = str[i];
		i++;
	}
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

	env_order = ft_calloc(arr_len(envp), sizeof(char *)); // -1 de menos 1 var +1 de str nula = 0
	if (!env_order)
		return (NULL);
	i = 0;
	while (i < arr_len(envp) - 1) // -1 porque exp tem menos 1 var que o env (não tem o "_=")
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
		if (!var_with_quotes)
		{
			free_arr(env_order);
			return (NULL);
		}
		ft_lstadd_back(&exp, ft_lstnew(ft_strjoin("declare -x ", var_with_quotes)));
		free(var_with_quotes);
		i++;
	}
	free_arr(env_order);
	return (exp);
}

int	flag_n(char *arg)
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

void	update_pwd_env(char *path, t_list **env)
{
	t_list	*temp_env;
	char	*new_oldpwd;

	temp_env = *env;
	while (temp_env != NULL)
	{
		if (ft_strncmp("PWD=", temp_env->content, 4) == 0)
		{
			new_oldpwd = ft_strjoin("OLD", temp_env->content);
			free(temp_env->content);
			temp_env->content = ft_strjoin("PWD=", path);
		}
		temp_env = temp_env->next;
	}
	temp_env = *env;
	while (temp_env != NULL)
	{
		if (ft_strncmp("OLDPWD=", temp_env->content, 7) == 0)
		{
			free(temp_env->content);
			temp_env->content = new_oldpwd;
		}
		temp_env = temp_env->next;
	}
	//error handling??
}

void	update_pwd_exp(char *path, t_list **exp)
{
	t_list	*temp_exp;
	char	*temp_new_oldpwd;
	char	*new_oldpwd;
	char	*path_with_quotes;

	temp_exp = *exp;
	while (temp_exp != NULL)
	{
		if (ft_strncmp("declare -x PWD=", temp_exp->content, 15) == 0)
		{
			temp_new_oldpwd = trim_beggining(temp_exp->content, "declare -x ");
			new_oldpwd = ft_strjoin("declare -x OLD", temp_new_oldpwd);
			free(temp_new_oldpwd);
			path_with_quotes = put_double_quotes(path);
			free(temp_exp->content);
			temp_exp->content = ft_strjoin("declare -x PWD=", path_with_quotes);
			free(path_with_quotes);
		}
		temp_exp = temp_exp->next;
	}
	temp_exp = *exp;
	while (temp_exp != NULL)
	{
		if (ft_strncmp("declare -x OLDPWD=", temp_exp->content, 18) == 0)
		{
			free(temp_exp->content);
			temp_exp->content = new_oldpwd;
		}
		temp_exp = temp_exp->next;
	}
	//error handling??
}

char	*join_all_args(t_cmd *cmd)
{
	int		i;
	char	*str1;
	char	*str2;

	str2 = ft_strdup(cmd->arg[1]);
	i = 1;
	while (cmd->arg[i] && cmd->arg[i + 1])
	{
		str1 = ft_strjoin(str2, " ");
		free(str2);
		str2 = ft_strjoin(str1, cmd->arg[i + 1]);
		free(str1);
		i++;
	}
	return (str2);
}

char	*ms_getenv(t_list *env, char *var)
{
	t_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->content, ft_strlen(var)) == 0)
			return (trim_beggining(temp->content, var));
		temp = temp->next;
	}
	return (NULL);
}

int	ms_cd(t_list **env, t_list **exp, t_cmd *cmd)
{
	char	*join_arg;
	char	*cwd;
	char	*get_env_home;
	
	if (cmd->n_arg == 1)
	{
		get_env_home = ms_getenv((*env), "HOME=");
		if (get_env_home == NULL)
		{
			ft_putendl_fd("Error: cd: no home directory found\n", 2);
			return (1);
		}
		else
		{
			chdir(get_env_home);
			update_pwd_env(get_env_home, env);
			update_pwd_exp(get_env_home, exp);
			free(get_env_home);
		}
	}
	else
	{
		join_arg = join_all_args(cmd);
		if (chdir(join_arg) == 0)
		{
			cwd = getcwd(NULL, 0);
			update_pwd_env(cwd, env);
			update_pwd_exp(cwd, exp);
			free(cwd);
		}
		else
		{
			ft_putendl_fd("Error: cd: Unable to execute cd\n", 2);
			return (1);
		}
		free(join_arg);
	}
	return (0);
}

int	ms_pwd()
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
}

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
			trim1 = trim_beggining(temp->content, "declare -x ");
			trim2 = trim_beggining(temp->next->content, "declare -x ");
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

//talvez no put_export excuso de usar o trim1 para comparar e posso fazer comparacao entre (*exp)->content e var_join
//ver se posso fazer algo do mesmo genero com o put_export_mid_end

void	put_export(t_list **exp, char *var)
{
	t_list	*new_node;
	char	*var_join;
	char	*trim1;

	var_join = ft_strjoin("declare -x ", var);
	if (!var_join)
		return;
	new_node = ft_lstnew(var_join);
	if (*exp == NULL)
	{
		*exp = new_node;
		return;
	}
	trim1 = trim_beggining((*exp)->content, "declare -x ");
	if (ft_strncmp(trim1, var, ft_strlen(var_join)) > 0)
		ft_lstadd_front(exp, new_node);
	else
		put_export_mid_end(exp, var, new_node);
	free(trim1);
}

char	*trim_value(char *var)
{
	int 	i;
	char	*trim;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	trim = ft_calloc(i + 2, sizeof(char));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, var, sizeof(char) * (i + 2));
	return (trim);
}

int	update_lst(t_list **lst, char *var, int b)
{
	t_list	*temp;
	char	*trim_var;
	int		len_cmp;
	char	*lst_cmp;
	
	if (!lst || !(*lst) || !var)
		return (0);
	temp = *lst;
	trim_var = trim_value(var);
	if (!trim_var)
		return (0);
	len_cmp = ft_strlen(trim_var);
	while (temp != NULL)
	{
		lst_cmp = trim_beggining(temp->content, "declare -x ");
		if (!lst_cmp)
		{
			free(trim_var);
			return (0);
		}
		if (!has_equal(temp->content))
			len_cmp = ft_strlen(lst_cmp);
		if (ft_strncmp(lst_cmp, trim_var, len_cmp) == 0)
		{
			free(lst_cmp);
			free(trim_var);
			if (b == 0 || b == 1)
				free(temp->content);
			if (b == 0)
				temp->content = ft_strdup(var);
			if (b == 1)
				temp->content = ft_strjoin("declare -x ", var);
			if (!temp->content)
				return (0);
			return (1);
		}
		free(lst_cmp);
		temp = temp->next;
	}
	free(trim_var);
	return (0);
}

void	print_exp(t_list *exp)
{
	while (exp != NULL)
	{
		printf("%s\n", (char *)exp->content);
		exp = exp->next;
	}
}

int	arg_valid(char *arg)
{
	int	i;

	if (!isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ms_export(t_list **env, t_list **exp, t_cmd *cmd)
{
	int		i;
	char	*arg_with_quotes;
	char	*dup;
	
	if (cmd->n_arg == 1)
		print_exp(*exp);
	i = 1;
	while (i < cmd->n_arg)
	{
		if (!arg_valid(cmd->arg[i]))
		{
			printf("Error: export: '%s': not a valid identifier\n", cmd->arg[i]);
			return (1);
		}
		else if (has_equal(cmd->arg[i]))
		{
			arg_with_quotes = put_double_quotes(cmd->arg[i]);
			if (!update_lst(env, cmd->arg[i], 0))
			{
				dup = ft_strdup(cmd->arg[i]);
				if (!dup)
					return (1);
				ft_lstadd_back(env, ft_lstnew(dup));
			}
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

//funtion that deletes either in env or exp the variable that wants to be unset if this variable has an "=" in the list

void	delete_var(t_list **lst, char *var)
{
	t_list	*temp;
	t_list	*to_delete;

	temp = *lst;
	if (!lst || !(*lst))
		return;
	if (ft_strncmp(temp->content, var, ft_strlen(var)) == 0)
	{
		*lst = (*lst)->next;
		free(temp->content);
		free(temp);
		return;
	}
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

//funtion that deletes in exp the variable that wants to be unset if this variable doesnt have an "=" in the list

int	delete_var_no_equal(t_list **lst, char *var_no_equal)
{
	t_list	*temp;
	t_list	*to_delete;

	temp = *lst;
	if (!lst || !(*lst))
		return (0);
	if (ft_strncmp(temp->content, var_no_equal, ft_strlen(temp->content)) == 0)
	{
		*lst = (*lst)->next;
		free(temp->content);
		free(temp);
		return (1);
	}
	while (temp->next && ft_strncmp(temp->next->content, var_no_equal, ft_strlen(temp->next->content)) != 0)
		temp = temp->next;
	if (temp->next && ft_strncmp(temp->next->content, var_no_equal, ft_strlen(temp->next->content)) == 0)
	{
		to_delete = temp->next;
		temp->next = temp->next->next;
		free(to_delete->content);
		free(to_delete);
		return (1);
	}
	return (0);
}

int	ms_unset(t_list **env, t_list **exp, t_cmd *cmd)
{
	char	*var_join_env;
	char	*var_join_exp_no_equal;
	char	*var_join_exp;
	int		i;

	i = 1;
	while (i < cmd->n_arg)
	{
		var_join_env = ft_strjoin(cmd->arg[i], "=");
		if (!var_join_env)
			return (1);
		var_join_exp_no_equal = ft_strjoin("declare -x ", cmd->arg[i]);
		if (!var_join_exp_no_equal)
		{
			free(var_join_env);
			return (1);
		}
		var_join_exp = ft_strjoin("declare -x ", var_join_env);
		if (!var_join_exp)
		{
			free(var_join_env);
			free(var_join_exp_no_equal);
			return (1);
		}
		delete_var(env, var_join_env);
		if (!delete_var_no_equal(exp, var_join_exp_no_equal))
			delete_var(exp, var_join_exp);
		free(var_join_env);
		free(var_join_exp_no_equal);
		free(var_join_exp);
		i++;
	}
	return (0);
}

int	ms_env(t_list *env)
{
	while (env != NULL)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (0);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_all()
{
	t_shell	*shell;
	
	shell = get_shell();
	free_atributes();
	free(shell->readline);
	free_lst(shell->env);
    free_lst(shell->exp);
}

void	ms_exit(t_shell **shell, t_cmd *cmd, int here)
{
	if (here)
	{
		free_all();
		printf("shell exit status ms_exit %d\n",(*shell)->exit_status);
		exit((*shell)->exit_status);
	}
	if (cmd->n_arg == 0)
	{
		free_all();
		exit((*shell)->exit_status);
	}
	else if (cmd->arg[1] && str_isdigit(cmd->arg[1]) && cmd->n_arg > 2)
	{
		printf("Error: exit: too many arguments\n");
		(*shell)->exit_status = 1;
	}
	else
	{
		if (cmd->arg[1] && !str_isdigit(cmd->arg[1]))
			printf("Error: exit: %s: numeric argument required\n", cmd->arg[1]);
		free_all();
		exit((*shell)->exit_status);
	}
}

void	free_lst(t_list *lst)
{
	t_list	*temp;
	
	if (!lst)
		return;
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->content);
		free(temp);
	}
}

int	build_ins(t_cmd *cmd)
{
	t_shell	*shell;

	shell = get_shell();
	if (!cmd || !cmd->arg || !cmd->arg[0])
		return (0);
	else if (ft_strncmp(cmd->arg[0], "echo", 5) == 0)
		shell->exit_status = ms_echo(cmd);
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		shell->exit_status = ms_cd(&shell->env, &shell->exp, cmd);
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
		printf("exit\n");
		ms_exit(&shell, cmd, 0);
	}
	else
		return (0);
	return (1);
}
