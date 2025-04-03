/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:50:31 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/02 20:26:08 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

static int	handle_outfile(t_cmd *cmd, int red_i)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = open(cmd->red[red_i]->str,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (error_open_outfile(cmd->fd_out, cmd->red[red_i]->str, cmd))
		return (0);
	return (1);
}

static int	handle_append(t_cmd *cmd, int red_i)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = open(cmd->red[red_i]->str,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (error_open_outfile(cmd->fd_out, cmd->red[red_i]->str, cmd))
		return (0);
	return (1);
}

static void	set_last_fd_in(t_cmd *cmd, char *last_in)
{
	if (last_in == NULL)
		return ;
	if (last_is_infile(cmd) == 0)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = get_fd_infile(last_in);
	}
}

static void	manage_redir_aux(char **last_in, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->red[++i])
	{
		if (cmd->red[i]->type == OUTFILE && !handle_outfile(cmd, i))
			break ;
		else if (cmd->red[i]->type == APPEND && !handle_append(cmd, i))
			break ;
		else if (cmd->red[i]->type == INFILE)
		{
			if (access(cmd->red[i]->str, F_OK) == -1)
			{
				printf("Error: %s: No such file or directory\n",
					cmd->red[i]->str);
				break ;
			}
			*last_in = cmd->red[i]->str;
		}
	}
}

//funtion that iterates through the reds in a command line and if the
//last input red is an infile updates the fd_in with its fd
//function that iterates through the reds in a command line and opens the output
//red files, storing the last one's fd in fd_out

//function that manages both infile red and output red

void	manage_redir(t_shell **shell)
{
	char	*last_in;
	int		j;

	j = 0;
	while ((*shell)->cmd[j])
	{
		last_in = NULL;
		manage_redir_aux(&last_in, (*shell)->cmd[j]);
		set_last_fd_in((*shell)->cmd[j++], last_in);
	}
}
