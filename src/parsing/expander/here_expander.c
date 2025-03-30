/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:34:35 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/30 00:21:24 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Expands variables in a here-document line.
 *
 * Iterates through the given `line`, processing `$` characters to expand 
 * variables. The expanded result is stored in a new string, replacing the 
 * original `line`. If no expansion occurs, `line` is set to `NULL`.
 *
 * @param line Pointer to the string being expanded.
 *
 * @return void.
 *
 * Auxiliary functions: process_dollar, update_str, free.
 */
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
