/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:37:17 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:37:20 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	assign_redirs(t_token	*token, t_redir	***redir)
{
	int		i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR)
		{
			(*redir)[i]->type = token->next->type;
			(*redir)[i]->str = token->next->str;
			if (ft_strncmp(token->str, "<<", 2) == 0)
				(*redir)[i++]->type = HERE_DOC;
			else if (!ft_strncmp(token->str, ">>", 2))
				(*redir)[i++]->type = APPEND;
			else if (!ft_strncmp(token->str, ">", 2))
				(*redir)[i++]->type = OUTFILE;
			else
				(*redir)[i++]->type = INFILE;
		}
		token = token->next;
	}
	(*redir)[i] = NULL;
}

t_redir **get_red(t_token	*token)
{
    int	redir_num;
    int	i;
	t_token	*tmp;
	t_redir **red;

	redir_num = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
			redir_num++;
		tmp = tmp->next;
	}
	red = ft_calloc(sizeof(t_redir *), redir_num + 1);
	if (!red)
		return ( NULL);
	i = 0;
	while (i < redir_num)
	{
		(red)[i] = ft_calloc(sizeof(t_redir), 1);
		if (!(red)[i++])
			return ( NULL);
	}
	assign_redirs(token, &red);
	return (red);
}
