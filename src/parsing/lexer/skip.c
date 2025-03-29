/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:12:54 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 03:04:57 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief edits index while char is space, tab or line break.
 *
 *auxiliar functions: get_shell.
 * @param i adress of index of the string where white spaces are to be skipped.
 * @return void.
 */
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

/**
 * @brief skips a substring between the first quote it finds.
 *
 *auxiliar functions: get_shell.
 * @param i adress of index of the string where a substring
 * between quotes is to be skipped.
 * @return 0 if quotes are closed 1 otherwise.
 */
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

/**
 * @brief skips a redirection in a string.
 *
 *auxiliar functions: get_shell, quote_skip, add_token.
 * @param i adress of index of the string where a word is to be skipped.
 * @return void.
 */
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

/**
 * @brief skips a redirection in a string.
 *
 * auxiliar functions: get_shell, add_token.
 * @param i adress of index of the string where a redir is to be skipped.
 * @return void.
 */
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
