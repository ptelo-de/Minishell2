/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:08:13 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 02:53:12 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if commandline has closed single and double quotes.
 * 
 * In case of error quotes error is printed in stderr.
 * auxiliar functons: quote_skip, ft_putendl_fd, get_shell
 * @return 0 if success 1 if error.
 */
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

/**
 * @brief builds list of tokens and adds it to statuc t_shell.
 *
 * tokens are separated according to bash manual.
 * They are stored in a t_token linked list and added to get_shell()
 * returned static t_shell structure at it's token attribute.
 * 
 * auxiliar functons: get_shell, quotes_check, white_space_skip, add_token
 * redir_skip, word_skip.
 * @return void.
 */
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
