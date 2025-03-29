/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:08:13 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:23:53 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	quotes_check(void)
{
	t_shell	*shell;
	int		i;

	shell = get_shell();
	i = 0;
	while (shell->readline[i])
	{
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			if (quote_skip(&i) == 1)
			{
				ft_putendl_fd("quotes error", 2);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

int	lexer(void)
{
	t_shell	*shell;
	int		i;

	shell = get_shell();
	i = 0;
	if (quotes_check() == 1)
		return (1);
	while (shell->readline[i])
	{
		white_space_skip(&i);
		if (shell->readline[i] == '|')
			add_token(i++, 1, PIPE);
		else if (shell->readline[i] == '<' || shell->readline[i] == '>' )
			redir_skip(&i);
		else
			word_skip(&i);
	}
	return (0);
}
