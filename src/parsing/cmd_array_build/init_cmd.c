/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:04:54 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/03 23:39:24 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 * @brief Creates and initializes a new command structure from a token list.
 *
 * Allocates memory for a `t_cmd` structure and initializes its fields. 
 * It sets default values for process ID (`pid`), input/output file descriptors 
 * (`fd_in`, `fd_out`), and output error flag (`out_error`). Then, it retrieves 
 * the command arguments and redirections from the given `token` list.
 *
 * If memory allocation fails or no arguments are 
 * found, the function returns `NULL`.
 *
 * @param token The token list from which to extract command data.
 *
 * @return A pointer to the newly created `t_cmd` 
 * structure, or `NULL` on failure.
 *
 * Auxiliary functions: ft_calloc, get_args, get_red.
 */
t_cmd	*get_next_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->out_error = 0;
	get_args(token, cmd);
	if (!cmd->arg)
	{
		return (NULL);
	}
	cmd->red = get_red(token);
	return (cmd);
}

/**
 * @brief Advances the token pointer to the next command token.
 *
 * Iterates through the token list until it reaches a token of type `PIPE`, 
 * indicating the end of the current command. If a `PIPE` token is found, 
 * the pointer is moved to the next token after the pipe.
 *
 * @param token A pointer to the token pointer, which will be updated.
 *
 * @return void.
 */
void	get_next_cmd_token(t_token **token)
{
	while (*token && (*token)->type != PIPE)
		*token = (*token)->next;
	if (*token)
		(*token) = (*token)->next;
}

/**
 * @brief Counts the number of commands in a token list.
 *
 * Iterates through the token list and counts the number of commands. 
 * Commands are separated by `PIPE` tokens, so the function increments 
 * the count each time a `PIPE` token is encountered. The function assumes 
 * at least one command is present.
 *
 * @param tokens The token list to process.
 *
 * @return The number of commands found in the token list.
 */
int	count_cmds(t_token	*tokens)
{
	int	cmd_num;

	cmd_num = 1;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
			cmd_num++;
		tokens = tokens->next;
	}
	return (cmd_num);
}

/**
 * @brief Initializes the command structures from the token list.
 *
 * Determines the number of commands in the token list and allocates memory 
 * for the `cmd` array in the shell structure. It then iterates through the 
 * tokens, extracting and storing each command structure in the array.
 *
 * If memory allocation fails, the function returns 1. Otherwise, it returns 0.
 *
 * @return 0 on success, 1 on memory allocation failure.
 *
 * Auxiliary functions: count_cmds, get_shell, 
 * ft_calloc, get_next_cmd, get_next_cmd_token.
 */
int	init_cmd(void)
{
	int		cmd_num;
	t_token	*tmp;
	int		i;
	size_t	size_p;

	cmd_num = count_cmds(get_shell()->tokens);
	size_p = sizeof(t_cmd *);
	get_shell()->cmd = ft_calloc(cmd_num + 1, size_p);
	if (get_shell()->cmd == NULL)
		return (1);
	tmp = get_shell()->tokens;
	get_shell()->cmd[0] = get_next_cmd(tmp);
	i = 1;
	while (i < cmd_num)
	{
		get_next_cmd_token(&tmp);
		get_shell()->cmd[i++] = get_next_cmd(tmp);
	}
	get_shell()->cmd[i] = NULL;
	return (0);
}
