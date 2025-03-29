/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:31:50 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 03:32:55 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	expand_quote(int *i, char **update, char *src, char quote_char)
{
	int	len;

	len = 0;
	while (src && src[++len])
	{
		if (quote_char == '\'')
		{
			if (src[len] == '\'')
				break ;
			update_str(update, src, len, 1);
		}
		if (quote_char == '\"')
		{
			if (src[len] == '$' && src[len + 1] != '\"')
				process_dollar(&len, src + len, update);
			else if (src[len] == '$' && src[len + 1] == '\"')
				update_str(update, src, len++, 1);
			if (src[len] != '\"')
				update_str(update, src, len, 1);
			else if (src[len] == '\"')
				break ;
		}
	}
	*i += len;
}

/**
 * @brief expands the node passed as parramether
 *
 * @param tmp adress of a shell->tokens node, shell 
 * is returned from get_shell function.
 * @param update buffer of expander token, must be NULL.
 *auxiliar functions: expand_quote, process_dollar, update_str, free.
 * @return void.
 */
void	expand_node(t_token **tmp, char	*update)
{
	int	i;

	i = 0;
	while ((*tmp)->str && (*tmp)->str[i])
	{
		if ((*tmp)->str[i] == '\'' || (*tmp)->str[i] == '\"')
		{
			(*tmp)->type = QUOTE;
			expand_quote(&i, &update, (*tmp)->str + i, (*tmp)->str[i]);
			i++;
		}
		else if ((*tmp)->str[i] == '$')
		{
			(*tmp)->type = DOLLAR;
			process_dollar(&i, (*tmp)->str + i, &update);
		}
		else
			update_str(&update, (*tmp)->str, i++, 1);
	}
	if ((*tmp)->str)
		free((*tmp)->str);
	if (update)
		(*tmp)->str = update;
	else
		(*tmp)->str = NULL;
}

/**
 * @brief edits shell->tokens list so that each node is expanded
 * according bash rule.
 *
 *auxiliar functions: get_shell, expand_node, clear_empty_token.
 * @return void.
 */
void	expander(void)
{
	t_token	*tmp;

	if (!get_shell() || !get_shell()->tokens)
		return ;
	tmp = get_shell()->tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand_node(&tmp, NULL);
		}
		tmp = tmp->next;
	}
	clear_empty_token();
}
