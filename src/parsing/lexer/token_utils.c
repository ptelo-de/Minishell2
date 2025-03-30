/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:17:50 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 03:15:28 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief allocates new token with instruction from paramethers and
 * adds it to the end to shell->token list, which is returned by get_shell.
 *
 *auxiliar functions: get_shell, ft_calloc, free_atributes, ft_putendl_fd,
 *exit, free_atributes, ft_substr, tokenlast.
 * in case of memory allocation error, get_shell() memmory is freed,
 * error message is printed in stderr and program exits.
 * @param start index where substring of readline must start;
 * @param len length of the substring of readline to create;
 * @return void.
 */
void	add_token(int start, int len, t_type type)
{
	t_shell	*shell;
	t_token	*token;

	shell = get_shell();
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		ft_putendl_fd("error allocating token", 2);
		free_atributes();
		exit(1);
	}
	token->type = type;
	token->str = ft_substr(shell->readline, start, len);
	token->next = NULL;
	token->prev = tokenlast(shell->tokens);
	if (token->prev)
		token->prev->next = token;
	else
		shell->tokens = token;
}

/**
 * @param first first node of t_token list.
 * @return last node of that t_token list.
 */
t_token	*tokenlast(t_token *first)
{
	t_token	*token;

	token = first;
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
