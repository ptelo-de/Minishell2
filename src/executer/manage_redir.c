/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:50:31 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 17:10:00 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

//function that receives the name of the last infile and opens
//it to return its fd

static int	get_fd_infile(char *infile)
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

//fucntion that checks if the last input red is an infile

static int	last_is_infile(t_cmd *cmd)
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

//funtion that iterates through the reds in a command line and if the
//last input red is an infile updates the fd_in with its fd
//function that iterates through the reds in a command line and opens the output
//red files, storing the last one's fd in fd_out

//function that manages both infile red and output red

void	manage_redir(t_shell **shell)
{
	char	*last_in;
	int		i;
	int		j;

	j = 0;
	while ((*shell)->cmd[j])
	{
		i = 0;
		while ((*shell)->cmd[j]->red[i])
		{
			if ((*shell)->cmd[j]->red[i]->type == OUTFILE)
			{
				if ((*shell)->cmd[j]->fd_out > 2)
					close((*shell)->cmd[j]->fd_out);
				(*shell)->cmd[j]->fd_out = open((*shell)->cmd[j]->red[i]->str,
						O_WRONLY | O_TRUNC | O_CREAT, 0644);
				if (error_open_outfile((*shell)->cmd[j]->fd_out,
						(*shell)->cmd[j]->red[i]->str))
					break ;
			}
			else if ((*shell)->cmd[j]->red[i]->type == APPEND)
			{
				if ((*shell)->cmd[j]->fd_out > 2)
					close((*shell)->cmd[j]->fd_out);
				(*shell)->cmd[j]->fd_out = open((*shell)->cmd[j]->red[i]->str,
						O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (error_open_outfile((*shell)->cmd[j]->fd_out,
						(*shell)->cmd[j]->red[i]->str))
					break ;
			}
			else if ((*shell)->cmd[j]->red[i]->type == INFILE)
			{
				if (access((*shell)->cmd[j]->red[i]->str, F_OK) == -1)
				{
					printf("Error: %s: No such file or directory\n",
						(*shell)->cmd[j]->red[i]->str);
					break ;
				}
				last_in = (*shell)->cmd[j]->red[i]->str;
			}
			i++;
		}
		if (last_is_infile((*shell)->cmd[j]) == 0)
		{
			if ((*shell)->cmd[j]->fd_in != 0)
				close((*shell)->cmd[j]->fd_in);
			(*shell)->cmd[j]->fd_in = get_fd_infile(last_in);
		}
		j++;
	}
}
