/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:41:58 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:42:09 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_cmd_redir(t_cmd **cmd)
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

void free_cmds(void)
{
	int k;

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
