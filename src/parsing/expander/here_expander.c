/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:39:22 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:39:36 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	here_expander(char **line)
{
	int i;
	char *update;

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
