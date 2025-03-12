
#include "parsing.h"
//$a $b "aaaaaaaaaaaaaaa $c" 'aaaaaaaaa""'

char *get_value(char *name)
{
    t_shell *shell;
    t_list *tmp;
    size_t name_len;

	shell = get_shell();
    if (!name || !(shell) || !(shell->env))
    {
        return NULL;
    }
    tmp = shell->env;
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
	t_shell	*shell;
	char *aux;

	shell = get_shell();
	aux = ft_itoa(shell->exit_status);
	//printf("itoa exit status %d\n", shell->exit_status);
	update_str(update, aux, 0, safe_strlen(aux));
	if (aux)
		free(aux);
}

void	process_dollar(int *len, char *src, char **update)
{
	int i;
	char *aux;
	char *var_name;
	char *value;

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
	{
		i = 1;
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
		i--;
		var_name = ft_substr(src, 1, i);
		value = get_value(var_name);
		if (value)
		{

		aux = ft_strdup(*update);
		if (*update)
			free(*update);
		*update = ms_strjoin(aux, get_value(var_name));
		if (aux)
			free(aux);
		}
		*len = *len + i + 1;
		if (var_name)
			free(var_name);
	}
}
void expand_quote(int *i, char **update, char *src)
{
	char quote;
	int len;

	quote = *src;
	len = 1;
	while (src && src[len])
	{
		if (quote == '\'')
		{
			if (src[len] == '\'')
				break;
			update_str(update, src, len, 1);
		}
		if (quote == '\"')
		{
			if (src[len] == '$')
				process_dollar(&len, src + len, update);
			if (src[len] != '\"')
				update_str(update, src, len, 1);
			else if (src[len] == '\"')
				break;
		}
		len++;
	}
	*i += len;
}
void	expand_node(t_token **tmp)
{

	int i;
	char *update;

	update = NULL;
	i = 0;
	while ((*tmp)->str && (*tmp)->str[i])
	{
		if ((*tmp)->str[i] == '\'' || (*tmp)->str[i] == '\"')
			expand_quote(&i, &update, (*tmp)->str + i++);
		else if ((*tmp)->str[i] == '$')
			process_dollar(&i, (*tmp)->str + i, &update);
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
void expander(void)
{
	t_token *tmp;
	t_shell *shell;

	shell = get_shell();
	if (!shell || !shell->tokens)
		return;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand_node(&tmp);
		}
		tmp = tmp->next;
	}
	clear_empty_token();
}

