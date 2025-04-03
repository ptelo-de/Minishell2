/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:00:04 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/03 23:42:23 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/**
 * @brief Checks if a token is an argument.
 *
 * Determines if the given `token` is of type `WORD`, `QUOTE`, or `DOLLAR`, 
 * and ensures that it is not preceded by a redirection token (`REDIR`). 
 * If both conditions are met, the token is considered an argument.
 *
 * @param token The token to check.
 *
 * @return 1 if the token is an argument, otherwise 0.
 */
int	is_arg(t_token *token)
{
	if ((token->type == WORD || \
	token->type == QUOTE || token->type == DOLLAR) \
	&& (!token->prev || token->prev->type != REDIR))
	{
		return (1);
	}
	return (0);
}

/**
 * @brief Assigns arguments from tokens to the argument array.
 *
 * Iterates through the linked list of tokens and assigns the `str` of 
 * tokens that are arguments (as determined by `is_arg`) to the `args` array. 
 * The loop stops when a token of type `PIPE` is encountered, and the last 
 * element of `args` is set to `NULL`.
 *
 * @param tokens The list of tokens to process.
 * @param args The array where the argument strings are stored.
 *
 * @return void.
 *
 * Auxiliary functions: is_arg.
 */
void	assign_args(t_token	*tokens, char	***args)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (is_arg(tokens))
			(*args)[i++] = tokens->str;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
}

/**
 * @brief Extracts and assigns command arguments from the token list.
 *
 * Iterates through the given token list until a `PIPE` token is encountered, counting 
 * the number of valid arguments. Allocates memory for the command's argument array 
 * and assigns the extracted arguments to it.
 *
 * @param token The starting token in the list.
 * @param cmd The command structure where arguments will be stored.
 *
 * @return void.
 *
 * Auxiliary functions: is_arg, ft_calloc, assign_args.
 */
void	get_args(t_token *token, t_cmd *cmd)
{
	t_token	*tmp;
	int		arg_num;

	tmp = token;
	arg_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_arg(tmp))
			arg_num++;
		tmp = tmp->next;
	}
	cmd->arg = ft_calloc(sizeof(char *) \
				* (arg_num + 1), 1);
	if (!(cmd->arg))
		return ;
	assign_args(token, &cmd->arg);
	cmd->n_arg = arg_num;
}
