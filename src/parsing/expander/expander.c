
#include "parsing.h"

size_t safe_strlen(const char *s)
{
	int i;

	if (!s) 
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);	
}

char	*ms_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	join = malloc((safe_strlen(s1) + safe_strlen(s2) + 1) * (sizeof(char)));
	if (join == 0)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}

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

void	process_dollar(int *len, char *src, char **update)
{
	int i;
	char *aux;
	char *auxx;

	if (!ft_isalpha(src[1]) && src[1] != '_')
	{
		aux = *update;
		*update= ms_strjoin(aux, "$");
		if (aux)
			free(aux);
		(*len)++;
		return;
	}
	else
	{
		i = 1;
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
		auxx = ft_substr(src, 1, i);
		aux = *update;
		*update = ms_strjoin(aux, get_value(auxx));
		if (aux)
			free(aux);
		if (auxx)
			free(auxx);
		*len = *len + i + 1;
	}
}
void expand_quote(int *i, char **update, char *src)
{
	char quote;
	int len;
	char *aux;
	char *auxx;

	quote = *src;
	len = 0;
	while (src[len])
	{
		if (quote == '\'' && len > 0 && src[len] == '\'')
		{
			auxx = ft_substr(src, *i + 1, len - 1);
			aux = *update;
			*update = ms_strjoin(aux, auxx);
			if (aux)
				free(aux);
			if (auxx)
				free(auxx);
			break;
		}
		if (quote == '\"' &&  len > 0 && (src[len] == '\"' || src[len] == '$'))
		{
			if (quote == '\"' && src[len] == '$')
				process_dollar( &len ,src + len, update);
			else
			{
				auxx = ft_substr(src, *i + 1, len);
				aux = *update;
				*update = ms_strjoin(aux, auxx);
				if (aux)
					free(aux);
				if (auxx)
					free(auxx);
				break;
			}
		}
		len++;
	}
	*i += len;
}


void expander(void) // falta fazer funçao para limpar nodes com strings vazias, que foram expandidas para null
{
	t_token *tmp;
	t_shell *shell;
	int i;
	char *update;
	char *aux;

	shell = get_shell();
	if (!shell || !shell->tokens)
		return;
	tmp = shell->tokens;
	update = NULL;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			i = 0;
			while (tmp->str[i])
			{
				if (tmp->str[i] == '\'' || tmp->str[i] == '\"')
				{
					expand_quote(&i, &update, tmp->str + i);
				}
				else if (tmp->str[i] == '$')
					process_dollar(&i, tmp->str + i, &update);
				else
				{
					i++;
					aux = update;
					update = ms_strjoin(aux, &tmp->str[i]);
					if (aux)
						free(aux);
				}
			}
			if (update)
				tmp->str = update;
			else
				tmp->str = NULL;
		}
		tmp = tmp->next;
	}
}
