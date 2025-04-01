/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:48:28 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 16:52:33 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that checks if there's an invalid infile in it's command line

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

//open outfile error function

int	error_open_outfile(int fd_outfile, char *name_outfile)
{
	DIR	*aux;

	aux = opendir(name_outfile);
	if (aux != NULL)
	{
		printf("%s: is a directory\n", name_outfile);
		closedir(aux);
		return (1);
	}
	if (fd_outfile == -1 || access(name_outfile, W_OK) == -1)
	{
		printf("Error opening outfile: %s\n", name_outfile);
		return (1);
	}
	return (0);
}

//function that checks if a command is a build_in

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

//fucntion that turns the env list back to an array

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
