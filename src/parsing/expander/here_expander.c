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
