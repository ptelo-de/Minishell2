/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creathe_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:51:58 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 23:43:04 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Finds and splits the PATH environment variable.
 *
 * Searches the `envp` array for the "PATH=" variable and splits its value
 * by ':' into an array of directories. If not found, uses the shell’s
 * private path as a fallback.
 *
 * @param envp the array of environment variables.
 * 
 * @return a newly allocated array of directory paths, 
 * or NULL if PATH is not found.
 */
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

/**
 * @brief Generates a path prefix by joining a directory with '/'.
 *
 * If a directory from the PATH is provided, it joins it with a slash.
 * Otherwise, uses the current working directory as the base path.
 *
 * @param path_env array of PATH directories (can be NULL).
 * @param path_env_i the current directory in PATH to join (can be NULL).
 * 
 * @return a newly allocated string representing the path prefix.
 */
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

/**
 * @brief Attempts to resolve the full path to an executable command.
 *
 * If the command is directly executable, returns it as-is.
 * Otherwise, searches for it in each directory of the PATH variable
 * and returns the first match that is executable.
 *
 * @param function the command or program name to locate.
 * @param envp the environment variables used to locate PATH.
 * 
 * @return a newly allocated string with the full executable path, or NULL if not found.
 */
char	*create_path(char *function, char **envp)
{
	int		i;
	char	**path_env;
	char	*path_join;
	char	*path;

	if (access(function, X_OK) == 0)
		return (function);
	path_env = find_path(envp);
	i = 0;
	while (path_env && i <= arr_len(path_env))
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
		i++;
	}
	free_arr(path_env);
	return (NULL);
}
