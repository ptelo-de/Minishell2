/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_atributess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:25:38 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:26:35 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tokens(void)
{
	t_shell	*shell;
	t_token	*next;

	shell = get_shell();
	while (shell->tokens)
	{
		next = shell->tokens->next;
		if (shell->tokens->str)
		{
			free(shell->tokens->str);
			shell->tokens->str = NULL;
		}
		free(shell->tokens);
		shell->tokens = NULL;
		shell->tokens = next;
	}
	shell->tokens = NULL;
}

void	free_atributes(void)
{
	free_tokens();
	free_cmds();
}
