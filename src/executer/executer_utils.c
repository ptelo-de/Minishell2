/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:48:28 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 17:04:49 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Checks if there is an invalid infile in the command redirections.
 *
 * Iterates through the command's redirections and returns 1 if any `INFILE`
 * does not exist (i.e., fails `access` with `F_OK`).
 *
 * @param cmd the command whose redirections are checked.
 * 
 * @return 1 if an invalid infile is found, 0 otherwise.
 */
int	infile_error(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->red[i])
	{
		if (cmd->red[i]->type == INFILE)
		{
			if (access(cmd->red[i]->str, F_OK) == -1)
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks for errors when opening an outfile.
 *
 * Detects if the target is a directory or if the file cannot be opened
 * or written to. Sets `cmd->out_error` in case of failure.
 *
 * @param fd_outfile the file descriptor returned by open.
 * @param name_outfile the name of the outfile.
 * @param cmd the command being processed (to set out_error flag).
 * 
 * @return 1 if an error occurred, 0 otherwise.
 */
int	error_open_outfile(int fd_outfile, char *name_outfile, t_cmd *cmd)
{
	DIR	*aux;

	aux = opendir(name_outfile);
	if (aux != NULL)
	{
		printf("%s: is a directory\n", name_outfile);
		closedir(aux);
		cmd->out_error = 1;
		return (1);
	}
	if (fd_outfile == -1 || access(name_outfile, W_OK) == -1)
	{
		printf("Error opening outfile: %s\n", name_outfile);
		cmd->out_error = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Determines if a command is a built-in shell command.
 *
 * Checks whether the command name matches one of the supported built-ins:
 * `cd`, `echo`, `pwd`, `export`, `unset`, `env`, or `exit`.
 *
 * @param cmd the command to check.
 * 
 * @return 1 if the command is a built-in, 0 otherwise.
 */
int	is_build_in(t_cmd *cmd)
{
	if (!cmd || !cmd->arg || !cmd->arg[0])
		return (0);
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "exit", 5) == 0)
		return (1);
	return (0);
}

/**
 * @brief Converts a linked list of environment variables to a string array.
 *
 * Allocates and returns a NULL-terminated array of strings, duplicating
 * each element from the environment list. Used when executing external commands.
 *
 * @param env the environment list to convert.
 * 
 * @return a newly allocated array of environment strings, or NULL on failure.
 */
char	**make_env_arr(t_list *env)
{
	t_list	*temp;
	char	**env_arr;
	int		i;

	temp = env;
	i = ft_lstsize(env);
	env_arr = malloc(sizeof(char *) * (i + 1));
	if (!env_arr)
		return (NULL);
	temp = env;
	i = 0;
	while (temp != NULL)
	{
		env_arr[i] = ft_strdup(temp->content);
		if (!env_arr[i])
		{
			free_arr(env_arr);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
