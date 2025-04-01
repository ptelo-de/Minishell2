/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creathe_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:51:58 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 01:17:23 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//fucntion that finds the path env variable

static char	**find_path(char **envp)
{
	int		i;
	char	*path_trim;
	char	**path_env;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_trim = trim_prefix(envp[i], "PATH=");
			path_env = ft_split(path_trim, ':');
			free(path_trim);
			return (path_env);
		}
		i++;
	}
	if (get_shell()->private_path != NULL)
		return (ft_split(get_shell()->private_path, ':'));
	return (NULL);
}

//fucntion that gets the joining of path and '/', the path depending if
//it's a system command or a 'program' that we want to execute

static char	*get_path_join(char **path_env, char *path_env_i)
{
	char	*path_join;
	char	*cwd;

	if (path_env && path_env_i)
		path_join = ft_strjoin(path_env_i, "/");
	else
	{
		cwd = getcwd(NULL, 0);
		path_join = ft_strjoin(cwd, "/");
		free(cwd);
	}
	return (path_join);
}

//fucntion that checks and finds the path to execute a command/program

char	*create_path(char *function, char **envp)
{
	int		i;
	char	**path_env;
	char	*path_join;
	char	*path;

	path_env = find_path(envp);
	i = arr_len(path_env);
	if (!path_env)
		return (NULL);
	while (i >= 0)
	{
		path_join = get_path_join(path_env, path_env[i]);
		path = ft_strjoin(path_join, function);
		free(path_join);
		if (access(path, X_OK) == 0)
		{
			free_arr(path_env);
			return (path);
		}
		free(path);
		i--;
	}
	free_arr(path_env);
	return (NULL);
}
