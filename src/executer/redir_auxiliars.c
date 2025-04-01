/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_auxiliars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:18:12 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 18:35:35 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

//fucntion that checks if the last input red is an infile

int	last_is_infile(t_cmd *cmd)
{
	int		i;
	int		b;

	i = 0;
	b = 1;
	while (cmd->red[i])
	{
		if (cmd->red[i]->type == INFILE)
			b = 0;
		else if (cmd->red[i]->type == HERE_DOC)
			b = 1;
		i++;
	}
	return (b);
}

//function that receives the name of the last infile and opens
//it to return its fd

int	get_fd_infile(char *infile)
{
	int		fd_infile;

	fd_infile = open(infile, O_RDONLY);
	if (fd_infile == -1)
	{
		printf("Error opening infile: %s\n", infile);
		return (-1);
	}
	return (fd_infile);
}
