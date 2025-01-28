
#include "parsing.h"
//$a $b "aaaaaaaaaaaaaaa $c" 'aaaaaaaaa""'

void clear_empty_token(void);
char	*ms_strjoin(char const *s1, char const *s2);
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
		auxx = ft_substr(src, 0, 2);
		aux = ft_strdup(*update);
		if (*update)
			free(*update);
		*update= ms_strjoin(aux, auxx);
		if (aux)
			free(aux);
		if (auxx)
			free(auxx);
		*len += 2;
		return;
	}
	else
	{
		i = 1;
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
		i--;
		auxx = ft_substr(src, 1, i);
		aux = ft_strdup(*update);
		if (*update)
			free(*update);
		*update = ms_strjoin(aux, get_value(auxx));
		if (aux)
			free(aux);
		if (auxx)
			free(auxx);
		*len = *len + i;
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
	while (src && src[len])
	{
		if (quote == '\'' && len > 0 && src[len] == '\'')
		{
			auxx = ft_substr(src, *i + 1, len - 1);
			aux = ft_strdup(*update);
			if (*update)
				free(*update);
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
				auxx = ft_substr(src, *i + 1, len - 1);
				aux = ft_strdup(*update);
				if (*update)
					free(*update);
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

void expander(void)
{
	t_token *tmp;
	t_shell *shell;
	int i;
	char *update;
	char *aux;
	char *auxx;

	shell = get_shell();
	if (!shell || !shell->tokens)
		return;
	tmp = shell->tokens;
	while (tmp)
	{
		update = NULL;
		if (tmp->type == WORD)
		{
			i = 0;
			while (tmp->str && tmp->str[i])
			{
				if (tmp->str[i] == '\'' || tmp->str[i] == '\"')
					expand_quote(&i, &update, tmp->str + i);
				else if (tmp->str[i] == '$')
					process_dollar(&i, tmp->str + i, &update);
				else
				{
					aux = ft_strdup(update);
					if (update)
						free(update);
					auxx = ft_substr(tmp->str, i, 1);
					update = ms_strjoin(aux, auxx);
					if (aux)
						free(aux);
					if (auxx)
						free(auxx);
					aux= NULL;
					auxx = NULL;
					i++;
				}
			}
			if (tmp->str)
				free(tmp->str);
			if (update)
				tmp->str = update;
			else
				tmp->str = NULL;
		}
		tmp = tmp->next;
	}
	clear_empty_token();
}

