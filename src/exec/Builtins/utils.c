/*#include "builtins.h"

void free_array(char **array)
{
    int i;
    i = 0;

    if (!array)
        return;
    while (array[i])
    {
        free(array[i]);
		array[i] = NULL;
        i++;
    }
    free(array);
}

void	bubble_sort(char **matrix)
{
	int		i; //this is to sort the export list
	int		j;
	char	*tmp;
	int		size;

	size = 0;
	while (matrix[size])
		size++;
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strcmp(matrix[j], matrix[j + 1]) > 0)
			{
				tmp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = tmp;
			}
		}
	}
}
*/