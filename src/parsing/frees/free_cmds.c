/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:27:26 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 03:21:11 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief frees a cmd->redir memory and sets all regarding
 * pointers to NULL.
 *
 *auxiliar functions: free.
 * @param cmd adress of pointer to t_cmd allocated struct.
 * @return void.
 */
void	free_cmd_redir(t_cmd **cmd)
{
	int	i;

	i = 0;
	while ((*cmd)->red && (*cmd)->red[i])
	{
		(*cmd)->red[i]->str = NULL;
		free ((*cmd)->red[i]);
		(*cmd)->red[i++] = NULL;
	}
	if ((*cmd)->red)
		free ((*cmd)->red);
	(*cmd)->red = NULL;
	i = 0;
	while ((*cmd)->here && (*cmd)->here[i])
	{
		(*cmd)->here[i]->str = NULL;
		free ((*cmd)->here[i]);
		(*cmd)->here[i++] = NULL;
	}
	if ((*cmd)->here)
		free ((*cmd)->here);
	(*cmd)->here = NULL;
}

/**
 * @brief frees shell->cmd memory and sets all regarding
 * pointers to NULL.
 *
 *auxiliar functions: get_shell, free.
 * @return void.
 */
void	free_cmds(void)
{
	int	k;

	k = 0;
	while (get_shell() && get_shell()->cmd \
			&& get_shell()->cmd[k])
	{
		if (get_shell()->cmd[k]->arg)
			free (get_shell()->cmd[k]->arg);
		get_shell()->cmd[k]->arg = NULL;
		free_cmd_redir(&(get_shell()->cmd[k]));
		free(get_shell()->cmd[k]);
		get_shell()->cmd[k++] = NULL;
	}
	if (get_shell() && get_shell()->cmd)
		free (get_shell()->cmd);
	get_shell()->cmd = NULL;
}
