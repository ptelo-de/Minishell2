/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:17:50 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:21:50 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
