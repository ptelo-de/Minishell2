/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:01:32 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:05:29 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	syntax_check(void)
{
	t_shell	*shell;
	t_token	*aux;

	shell = get_shell();
	if (!shell)
		return (1);
	if (!shell->tokens)
		return (1);
	aux = shell->tokens;
	while (aux)
	{
		if ((aux->type == PIPE && (!aux->prev || aux->prev->type != WORD \
			|| !aux->next || aux->next->type == PIPE)) || (aux->type == REDIR \
				&& (!aux->next || aux->next->type != WORD)))
		{
			ft_putendl_fd("syntax error", 2);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
/* 

[] if first token s a pipe then syntax error
[] cuidado com o ||
[] depois redir n posso ter um pipe
[] depois redir posso ter redir
[] depois de um pipe posso redir
[] posso nao ter nada antes da redir e é ok

 */