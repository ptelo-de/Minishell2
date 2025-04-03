/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_and_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:41:44 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 15:55:39 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Updates the PWD and OLDPWD environment variables.
 *
 * Searches through the environment list for the "PWD=" variable,
 * updates it with the new path, and sets "OLDPWD=" to the previous value of "PWD".
 *
 * @param new_pwd the new present working directory.
 * @param env pointer to the environment list.
 * 
 * @return void.
 */
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

/**
 * @brief Joins all arguments after `cd` into a single string.
 *
 * Useful when the directory name contains spaces and is split
 * across multiple arguments.
 *
 * @param cmd the command containing the arguments.
 * 
 * @return a newly allocated string with all arguments joined by spaces.
 */
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

/**
 * @brief Retrieves the value of an environment variable.
 *
 * Searches through the environment list for the specified variable
 * and returns its value without the prefix.
 *
 * @param env the environment list.
 * @param var the variable to look for (e.g. "HOME=").
 * 
 * @return pointer to the value part of the variable, or NULL if not found.
 */
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

/**
 * @brief Executes the `cd` command.
 *
 * Changes the current working directory to the one specified in the command.
 * If no argument is provided, it attempts to change to the HOME directory.
 * Updates the environment with the new PWD and OLDPWD values.
 *
 * @param shell the shell structure.
 * @param env pointer to the environment list.
 * @param cmd the command containing the arguments.
 * 
 * @return 0 if successful, 1 if an error occurred.
 */
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
		{
			free(join_arg);
			return (print_and_return("Error: cd: Unable to execute cd", 1));
		}
		new_pwd = getcwd(NULL, 0);
		free(join_arg);
	}
	chdir(new_pwd);
	update_pwd_env(new_pwd, env);
	free_lst(shell->exp);
	shell->exp = get_exp(make_env_arr(*env));
	return (free(new_pwd), 0);
}

/**
 * @brief Executes the `pwd` command.
 *
 * Prints the current working directory to standard output.
 *
 * @return 0 if successful, 1 if an error occurred.
 */
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
