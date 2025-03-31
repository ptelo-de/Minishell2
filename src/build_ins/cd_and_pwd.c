/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_and_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:41:44 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/29 20:27:32 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that updates OLD_PWD and PWD in env after executing cd

static void	update_pwd_env(char *new_pwd, t_list **env)
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
			temp_env->content = ft_strjoin("PWD=", new_pwd);
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
}

//function that joins all arguments 
//(for cd to execute when a directory has more than a word)

static char	*join_all_args(t_cmd *cmd)
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

//getenv for our env

static char	*ms_getenv(t_list *env, char *var)
{
	t_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->content, ft_strlen(var)) == 0)
			return (trim_prefix(temp->content, var));
		temp = temp->next;
	}
	return (NULL);
}

//cd function

int	ms_cd(t_shell *shell, t_list **env, t_cmd *cmd)
{
	char	*join_arg;
	char	*new_pwd;

	if (cmd->n_arg == 1)
	{
		new_pwd = ms_getenv((*env), "HOME=");
		if (new_pwd == NULL)
			return (print_and_return("Error: cd: no home directory found", 1));
	}
	else
	{
		join_arg = join_all_args(cmd);
		if (chdir(join_arg) == -1)
			return (print_and_return("Error: cd: Unable to execute cd", 1));
		new_pwd = getcwd(NULL, 0);
		free(join_arg);
	}
	chdir(new_pwd);
	update_pwd_env(new_pwd, env);
	free_lst(shell->exp);
	shell->exp = get_exp(make_env_arr(*env));
	free(new_pwd);
	return (0);
}

//pwd function

int	ms_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (print_and_return("Error: Failed to get current directory", 1));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
