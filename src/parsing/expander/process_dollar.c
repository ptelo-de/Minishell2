#include "parsing.h"

/* 
returns value o enviroment variable
if it exists, an empty string if the value is empty, 
and NULL if the variable does not exist.
 */

char *get_value(char *name)
{
    t_list *tmp;
    size_t name_len;

    if (!name || !(get_shell()) || !(get_shell()->env))
    {
        return NULL;
    }
    tmp = get_shell()->env;
    name_len = ft_strlen(name);

    while (tmp)
	{
        if (ft_strncmp(tmp->content, name, name_len) == 0 && ((char *)tmp->content)[name_len] == '=')
		{
            return ((char*)tmp->content + name_len + 1);
        }
        tmp = tmp->next;
    }
    return NULL;
}
void exit_status_expander( char **update)
{
	char *aux;

	aux = ft_itoa(get_shell()->exit_status);
	update_str(update, aux, 0, safe_strlen(aux));
	if (aux)
		free(aux);
}
void	expand_standard_dollar_format(int **pointer_add, char	*src, char **update)
{
		int	i;
		char	*var_name;
		char	*value;
		char	*aux;
		int	*len_pointer;

		i = 1;
		len_pointer = *pointer_add;
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
		i--;
		var_name = ft_substr(src, 1, i);
		value = get_value(var_name);
		if (value && value[0])
		{
			aux = ft_strdup(*update);
			if (*update)
				free(*update);
			*update = ms_strjoin(aux, value);
			if (aux)
				free(aux);
		}
		*len_pointer = *len_pointer + i + 1;
		if (var_name)
			free(var_name);
}
void	process_dollar(int *len, char *src, char **update)
{
	if (src[1] == '\"' || src[1] == '\'')
	{
		(*len)++;
		return;
	}
	if (!ft_isalpha(src[1]) && src[1] != '_' && src[1] != '?')
	{
		update_str(update, src, 0, 2);
		if (src[1] == '\0')
			(*len)++;
		else
			*len += 2;
	}
	else if (src[1] == '?')
	{
		exit_status_expander(update);
		*len +=2;
	}
	else
		expand_standard_dollar_format(&len, src, update);
}
