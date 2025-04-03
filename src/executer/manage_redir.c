/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:50:31 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 19:19:00 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

/**
 * @brief Opens an output file for truncation (overwrite mode).
 *
 * Closes any previously opened `fd_out`, then opens the target file
 * with `O_WRONLY | O_TRUNC | O_CREAT`. Handles errors with `error_open_outfile`.
 *
 * @param cmd the command whose redirection is being processed.
 * @param red_i the index of the redirection in the `cmd->red` array.
 * 
 * @return 1 if the file was opened successfully, 0 otherwise.
 */
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

/**
 * @brief Opens an output file in append mode.
 *
 * Closes any previously opened `fd_out`, then opens the target file
 * with `O_WRONLY | O_APPEND | O_CREAT`. Handles errors with `error_open_outfile`.
 *
 * @param cmd the command whose redirection is being processed.
 * @param red_i the index of the redirection in the `cmd->red` array.
 * 
 * @return 1 if the file was opened successfully, 0 otherwise.
 */
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

/**
 * @brief Updates `fd_in` with the last valid infile in the redirection list.
 *
 * If the last input redirection is an infile (and not a here_doc),
 * closes any existing `fd_in` and opens the new one with `get_fd_infile`.
 *
 * @param cmd the command to update.
 * @param last_in the path to the last infile found.
 * 
 * @return void.
 */
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

/**
 * @brief Processes all redirections in a command.
 *
 * Iterates through all redirections in the command. Opens outfiles and append files
 * and handles possible errors. If an input file is found, stores its name
 * in `last_in` to be opened later. Prints an error if an input file does not exist.
 *
 * @param last_in pointer to store the name of the last input file encountered.
 * @param cmd the command whose redirections are being handled.
 * 
 * @return void.
 */
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

/**
 * @brief Manages input and output redirections for all commands.
 *
 * For each command in the shell, processes redirections using `manage_redir_aux`
 * and sets `fd_in` to the last valid infile (if applicable).
 *
 * @param shell pointer to the shell structure.
 * 
 * @return void.
 */
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
