/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:50:31 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:14:35 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that receives the name of the last infile and opens it to return its fd

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

//funtion that iterates through the reds in a command line and if the last input red is an infile updates the fd_in with its fd

static void	handle_infile(t_cmd *cmd, t_shell **shell, int j)
{
	char	*last_in;
	int		i;

	i = 0;
	while (cmd->red[i])
	{
		if (cmd->red[i]->type == INFILE)
		{
			if (access(cmd->red[i]->str, F_OK) == -1)
			{
				printf("Error: %s: No such file or directory\n", cmd->red[i]->str);
				return;
			}
			last_in = cmd->red[i]->str;
		}
		i++;
	}
	if (last_is_infile(cmd) == 0)
	{
		if ((*shell)->cmd[j]->fd_in != 0)
			close((*shell)->cmd[j]->fd_in);
		(*shell)->cmd[j]->fd_in = get_fd_infile(last_in);
	}
}

//function that iterates through the reds in a command line and opens the output red files, storing the last one's fd in fd_out

static void	handle_outfile(t_cmd *cmd, t_shell **shell, int j)
{
	int	fd_outfile;
	int	i;

	fd_outfile = 1;
	i = 0;
	while (cmd->red[i])
	{
		if (cmd->red[i]->type == OUTFILE)
		{
			if (fd_outfile != 1)
				close(fd_outfile);
			fd_outfile = open(cmd->red[i]->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			error_open_outfile(fd_outfile, cmd->red[i]->str);
		}
		else if (cmd->red[i]->type == APPEND)
		{
			if (fd_outfile != 1)
				close(fd_outfile);
			fd_outfile = open(cmd->red[i]->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
			error_open_outfile(fd_outfile, cmd->red[i]->str);
		}
		i++;
	}
	(*shell)->cmd[j]->fd_out = fd_outfile;
}

//function that manages both infile red and output red

void	manage_redir(t_shell **shell)
{
	int		i;

	i = 0;
	while ((*shell)->cmd[i])
	{
		handle_infile((*shell)->cmd[i], shell, i);
		handle_outfile((*shell)->cmd[i], shell, i);
		i++;
	}
}