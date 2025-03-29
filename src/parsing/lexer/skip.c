/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:12:54 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:24:13 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	white_space_skip(int *i)
{
	t_shell	*shell;
	char	*s;

	shell = get_shell();
	s = shell->readline;
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' \
			|| s[*i] == '\n'))
	{
		*i = *i + 1;
	}
}

int	quote_skip(int *i)
{
	t_shell	*shell;
	char	c;

	shell = get_shell();
	c = shell->readline[*i];
	(*i)++;
	while (shell->readline[*i] && shell->readline[*i] != c)
		(*i)++;
	if (shell->readline[*i] == c)
	{
		(*i)++;
		return (0);
	}
	else
		return (1);
}

void	word_skip(int *i)
{
	t_shell	*shell;
	int		j;

	j = *i;
	shell = get_shell();
	while (shell->readline[*i] \
	&& shell->readline[*i] != '|' \
	&& shell->readline[*i] != ' ' \
	&& shell->readline[*i] != '\t' \
	&& shell->readline[*i] != '\n' \
	&& shell->readline[*i] != '<' \
	&& shell->readline[*i] != '>')
	{
		if (shell->readline[*i] == '\'' || shell->readline[*i] == '\"')
			quote_skip(i);
		else
			(*i)++;
	}
	if (*i - j)
		add_token(j, *i - j, WORD);
}

void	redir_skip(int *i)
{
	t_shell	*shell;
	int		j;

	j = *i;
	shell = get_shell();
	if (shell->readline[*i + 1] == shell->readline[*i])
	{
		(*i) = *i + 2;
		return (add_token(j, 2, REDIR));
	}
	add_token(j, 1, REDIR);
	(*i)++;
}
