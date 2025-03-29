/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:42:25 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:42:36 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

int quotes_check(void)
{
	t_shell *shell;
    int i;

    shell = get_shell();
    i = 0;
	while (shell->readline[i])
	{
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			if (quote_skip(&i) == 1)
			{
				ft_putendl_fd("quotes error", 2);
				return(1);
			}
		}
		else
			i++;
	}
	return (0);
}

int lexer(void)
{
    t_shell *shell;
    int i;

    shell = get_shell();
    i = 0;

	if (quotes_check() == 1)
		return (1);
    while(shell->readline[i])
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
