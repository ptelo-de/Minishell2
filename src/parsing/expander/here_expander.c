/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:34:35 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 01:36:45 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	here_expander(char **line)
{
	int		i;
	char	*update;

	update = NULL;
	i = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '$')
		{
			process_dollar(&i, *line + i, &update);
		}
		else
			update_str(&update, *line, i++, 1);
	}
	if (*line)
		free(*line);
	if (update)
		(*line) = update;
	else
		*line = NULL;
}
