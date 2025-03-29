/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:43:16 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/29 00:16:04 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void white_space_skip(int *i)
{
    t_shell *shell;
    char *s;

    shell = get_shell();
    s = shell->readline;
    while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' \
			|| s[*i] == '\n'))
	{
        *i = *i + 1;
	}
}

int quote_skip(int *i)
{
	t_shell *shell = get_shell();
	char c;

	c = shell->readline[*i];
	(*i)++;
	while ( shell->readline[*i] && shell->readline[*i] != c)
		(*i)++;
	if (shell->readline[*i] == c)
	{
		(*i)++;
		return (0);
	}
	else
		return(1);     
}

void word_skip(int *i)
{
	t_shell *shell;
	int j;

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
	if (*i -j)
		add_token(j, *i - j, WORD);
}
void redir_skip(int *i)
{
    t_shell *shell;
    int j;

    j = *i;
    shell = get_shell();
	if (shell->readline[*i + 1] == shell->readline[*i])
	{
		(*i) = *i + 2;
		return(add_token(j, 2, REDIR));
	}
	add_token(j, 1, REDIR);
	(*i)++;
}